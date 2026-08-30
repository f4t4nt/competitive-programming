/*
(a, b, c) = (1/4, -3, 1/2)

16-candidates: 44189
Solved.

Grid ('.' = empty):
 .  5  5  5 15 15  . 11  .  .  .  .  .
 .  .  .  5  . 15  . 11  .  . 11 11 11
15 15 15  5  . 15 15 11 11 11 11  . 11
15 16 15 15 15 15  8  8  8 12 12 12 11
15 16  .  .  8  8  8  .  8 12  6  6  6
15 16  . 16 16 16 16  .  8 12 12  .  6
 . 16 16 16  3  3 16 16  1  4 12  6  6
13 13 13 13 14  3 16  4  4  4 12 10 10
 7  7  7 13 14 16 16 12 12 12 12 10  .
 7  2  2 13 14 16 14 14 14 14  . 10  .
 7  7 13 13 14 14 14  .  9 14 14 10 10
 .  7 13  9  9  9  9  .  9 14  .  . 10
 .  . 13 13 13 13  9  9  9 14 10 10 10

Row sums:
Row 1: 56
Row 2: 64
Row 3: 135
Row 4: 162
Row 5: 93
Row 6: 133
Row 7: 115
Row 8: 129
Row 9: 138
Row 10: 120
Row 11: 139
Row 12: 89
Row 13: 123

min row sum = 56
max row sum = 162
answer = 9072
*/

#include <bits/stdc++.h>
using namespace std;

// ============================================================
// Config (actual puzzle)
// ============================================================
static constexpr int H = 13, W = 13;
static constexpr int NC = H * W;                 // 169
static constexpr int N  = 16;
static constexpr int WORDS = (NC + 63) / 64;     // 3
static constexpr int EXTRA = WORDS * 64 - NC;    // 23
static constexpr uint64_t LAST_KEEP = (EXTRA == 0) ? ~0ULL : (~0ULL >> EXTRA);

// ============================================================
// Bitmask over NC cells
// ============================================================
struct Mask {
    uint64_t w[WORDS];
    Mask() { for(int i=0;i<WORDS;i++) w[i]=0; }

    inline void set(int i) { w[i>>6] |= (1ULL << (i & 63)); }
    inline bool test(int i) const { return (w[i>>6] >> (i & 63)) & 1ULL; }

    inline int popcount() const {
        int s = 0;
        for(int i=0;i<WORDS;i++) s += __builtin_popcountll(w[i]);
        return s;
    }

    inline bool any() const {
        uint64_t acc = 0;
        for(int i=0;i<WORDS;i++) acc |= w[i];
        return acc != 0;
    }
    inline bool none() const { return !any(); }

    inline bool intersects(const Mask& o) const {
        for(int i=0;i<WORDS;i++) if(w[i] & o.w[i]) return true;
        return false;
    }

    inline Mask operator|(const Mask& o) const { Mask r; for(int i=0;i<WORDS;i++) r.w[i]=w[i]|o.w[i]; return r; }
    inline Mask operator&(const Mask& o) const { Mask r; for(int i=0;i<WORDS;i++) r.w[i]=w[i]&o.w[i]; return r; }
    inline Mask operator^(const Mask& o) const { Mask r; for(int i=0;i<WORDS;i++) r.w[i]=w[i]^o.w[i]; return r; }

    inline Mask& operator|=(const Mask& o){ for(int i=0;i<WORDS;i++) w[i] |= o.w[i]; return *this; }
    inline Mask& operator&=(const Mask& o){ for(int i=0;i<WORDS;i++) w[i] &= o.w[i]; return *this; }
    inline Mask& operator^=(const Mask& o){ for(int i=0;i<WORDS;i++) w[i] ^= o.w[i]; return *this; }

    inline Mask operator~() const {
        Mask r;
        for(int i=0;i<WORDS;i++) r.w[i] = ~w[i];
        r.w[WORDS-1] &= LAST_KEEP;
        return r;
    }

    // remove bits present in o
    inline Mask& operator-=(const Mask& o) {
        for(int i=0;i<WORDS;i++) w[i] &= ~o.w[i];
        w[WORDS-1] &= LAST_KEEP;
        return *this;
    }

    // is this a superset of o? (i.e., o subset of this)
    inline bool contains_all(const Mask& o) const {
        for(int i=0;i<WORDS-1;i++){
            if((w[i] & o.w[i]) != o.w[i]) return false;
        }
        return ((w[WORDS-1] & o.w[WORDS-1]) == (o.w[WORDS-1] & LAST_KEEP));
    }

    template<class F>
    inline void for_each_bit(F&& f) const {
        for(int k=0;k<WORDS;k++){
            uint64_t x = w[k];
            while(x){
                uint64_t b = x & -x;
                int bit = __builtin_ctzll(x);
                int idx = (k<<6) + bit;
                f(idx);
                x -= b;
            }
        }
    }

    inline bool operator==(const Mask& o) const {
        for(int i=0;i<WORDS;i++) if(w[i]!=o.w[i]) return false;
        return true;
    }
};

struct MaskHash {
    size_t operator()(Mask const& m) const noexcept {
        // simple mix
        size_t h = 1469598103934665603ULL;
        for(int i=0;i<WORDS;i++){
            uint64_t x = m.w[i];
            h ^= (size_t)x + 0x9e3779b97f4a7c15ULL + (h<<6) + (h>>2);
        }
        return h;
    }
};

static inline int id(int r, int c){ // 1-based
    return (r-1)*W + (c-1);
}
static inline pair<int,int> rc(int idx){ // -> 1-based
    return { idx/W + 1, idx%W + 1 };
}

// ============================================================
// Neighbors
// ============================================================
static Mask NEI[NC];

static void init_neighbors(){
    for(int r=1;r<=H;r++){
        for(int c=1;c<=W;c++){
            Mask m;
            int dr[4]={1,-1,0,0};
            int dc[4]={0,0,1,-1};
            for(int t=0;t<4;t++){
                int rr=r+dr[t], cc=c+dc[t];
                if(1<=rr && rr<=H && 1<=cc && cc<=W) m.set(id(rr,cc));
            }
            NEI[id(r,c)] = m;
        }
    }
}

// ============================================================
// Shape canonicalization (dihedral, normalize, key string)
// ============================================================
static inline pair<int,int> transform_xy(int x, int y, int k){
    switch(k){
        case 0: return { x,  y};
        case 1: return { x, -y};
        case 2: return {-x,  y};
        case 3: return {-x, -y};
        case 4: return { y,  x};
        case 5: return { y, -x};
        case 6: return {-y,  x};
        case 7: return {-y, -x};
    }
    return {x,y};
}

static inline vector<pair<int,int>> normalize_pts(vector<pair<int,int>> v){
    int minx=INT_MAX, miny=INT_MAX;
    for(auto &p: v){ minx=min(minx,p.first); miny=min(miny,p.second); }
    for(auto &p: v){ p.first-=minx; p.second-=miny; }
    sort(v.begin(), v.end());
    return v;
}

static inline string pts_key(const vector<pair<int,int>>& pts){
    // stable string key
    string s;
    s.reserve(pts.size()*6);
    for(auto [x,y]: pts){
        s.append(to_string(x));
        s.push_back(',');
        s.append(to_string(y));
        s.push_back(';');
    }
    return s;
}

struct ShapeCanon {
    string key;
    vector<pair<int,int>> canon_pts;
};

static ShapeCanon canonical_from_pts(const vector<pair<int,int>>& base){
    ShapeCanon best;
    best.key = "~";
    for(int k=0;k<8;k++){
        vector<pair<int,int>> tr;
        tr.reserve(base.size());
        for(auto [x,y]: base){
            auto [u,v] = transform_xy(x,y,k);
            tr.push_back({u,v});
        }
        auto norm = normalize_pts(move(tr));
        string key = pts_key(norm);
        if(key < best.key){
            best.key = key;
            best.canon_pts = move(norm);
        }
    }
    return best;
}

static ShapeCanon canonical_from_mask(const Mask& m){
    vector<pair<int,int>> pts;
    pts.reserve(64);
    m.for_each_bit([&](int cell){
        auto [r,c] = rc(cell);
        pts.push_back({c-1, r-1}); // (x,y)
    });
    return canonical_from_pts(pts);
}

static vector<vector<pair<int,int>>> all_variants_from_canon(const vector<pair<int,int>>& canon_pts){
    vector<vector<pair<int,int>>> vars;
    unordered_set<string> seen;
    seen.reserve(16);
    for(int k=0;k<8;k++){
        vector<pair<int,int>> tr;
        tr.reserve(canon_pts.size());
        for(auto [x,y]: canon_pts){
            auto [u,v] = transform_xy(x,y,k);
            tr.push_back({u,v});
        }
        auto norm = normalize_pts(move(tr));
        string key = pts_key(norm);
        if(seen.insert(key).second) vars.push_back(move(norm));
    }
    return vars;
}

static bool pts_connected(const vector<pair<int,int>>& pts){
    if(pts.empty()) return false;
    unordered_map<long long,int> idx;
    idx.reserve(pts.size()*2);
    auto key = [&](int x,int y)->long long{ return ( (long long)x<<32 ) ^ (unsigned)y; };

    for(int i=0;i<(int)pts.size();i++){
        idx[key(pts[i].first, pts[i].second)] = i;
    }

    vector<char> vis(pts.size(), 0);
    deque<int> q;
    q.push_back(0);
    vis[0]=1;
    int seen=1;

    static int dx[4]={1,-1,0,0};
    static int dy[4]={0,0,1,-1};

    while(!q.empty()){
        int u=q.front(); q.pop_front();
        int x=pts[u].first, y=pts[u].second;
        for(int t=0;t<4;t++){
            int nx=x+dx[t], ny=y+dy[t];
            auto it = idx.find(key(nx,ny));
            if(it==idx.end()) continue;
            int v=it->second;
            if(!vis[v]){
                vis[v]=1;
                seen++;
                q.push_back(v);
            }
        }
    }
    return seen==(int)pts.size();
}

static vector<string> parents_by_remove_one(const vector<pair<int,int>>& child_canon_pts,
                                           unordered_map<string, vector<pair<int,int>>>& out_pts_by_key){
    unordered_map<string, vector<pair<int,int>>> tmp;
    tmp.reserve(child_canon_pts.size()*2);

    for(size_t i=0;i<child_canon_pts.size();i++){
        vector<pair<int,int>> rem;
        rem.reserve(child_canon_pts.size()-1);
        for(size_t j=0;j<child_canon_pts.size();j++){
            if(j==i) continue;
            rem.push_back(child_canon_pts[j]);
        }
        auto can = canonical_from_pts(rem);

        // NEW: ensure parent shape is connected
        if(!pts_connected(can.canon_pts)) continue;

        tmp.emplace(can.key, can.canon_pts);
    }

    vector<string> keys;
    keys.reserve(tmp.size());
    for(auto &kv: tmp){
        keys.push_back(kv.first);
        out_pts_by_key.emplace(kv.first, kv.second);
    }
    sort(keys.begin(), keys.end());
    return keys;
}

// ============================================================
// Givens (decoded)
// ============================================================
static map<pair<int,int>, int> GIVENS = {
    {{1,5},15},{{2,8},11},{{3,2},15},{{3,4},5},{{3,7},15},{{3,9},11},{{3,11},11},
    {{4,5},15},{{4,8},8},{{4,10},12},{{4,12},12},{{5,2},16},{{5,6},8},{{5,11},6},
    {{6,4},16},{{6,13},6},{{7,3},16},{{7,5},3},{{7,7},16},{{7,9},1},{{7,11},12},
    {{8,1},13},{{8,10},4},{{9,3},7},{{9,8},12},{{9,12},10},{{10,2},2},{{10,4},13},
    {{10,6},16},{{10,9},14},{{11,3},13},{{11,5},14},{{11,7},14},{{11,10},14},{{11,12},10},
    {{12,6},9},{{13,9},9}
};

static vector<Mask> REQ(N+1), FIXED_OTHER(N+1);
static vector<int> FIXED_VAL(NC,0);

// ============================================================
// Placement cache: placements of shape_key for given k, respecting fixed non-k
// ============================================================
struct KeyHash {
    size_t operator()(const pair<int,string>& p) const noexcept {
        return std::hash<int>()(p.first) * 1315423911u ^ std::hash<string>()(p.second);
    }
};

static unordered_map<pair<int,string>, vector<Mask>, KeyHash> placements_cache;
static unordered_map<string, vector<pair<int,int>>> canon_pts_by_key;

// shape key -> integer id for memoization
static unordered_map<string,int> shape_id;
static int get_shape_id(const string& key){
    auto it = shape_id.find(key);
    if(it!=shape_id.end()) return it->second;
    int nid = (int)shape_id.size()+1;
    shape_id.emplace(key,nid);
    return nid;
}

static vector<Mask> compute_placements_for_shape(int k, const string& shape_key){
    auto cache_key = make_pair(k, shape_key);
    auto it = placements_cache.find(cache_key);
    if(it != placements_cache.end()) return it->second;

    auto it2 = canon_pts_by_key.find(shape_key);
    if(it2 == canon_pts_by_key.end()){
        placements_cache[cache_key] = {};
        return {};
    }
    const auto& canon_pts = it2->second;
    auto variants = all_variants_from_canon(canon_pts);

    vector<Mask> placements;
    placements.reserve(256);

    for(const auto& vpts : variants){
        int maxx=0, maxy=0;
        for(auto [x,y]: vpts){ maxx=max(maxx,x); maxy=max(maxy,y); }
        for(int dy=0; dy + maxy < H; dy++){
            for(int dx=0; dx + maxx < W; dx++){
                Mask m;
                for(auto [x,y]: vpts){
                    int rr = (y+dy)+1;
                    int cc = (x+dx)+1;
                    m.set(id(rr,cc));
                }
                if(m.intersects(FIXED_OTHER[k])) continue;   // can't cover cells fixed to other values
                if(!m.contains_all(REQ[k])) continue;        // must cover all k-fixed cells
                placements.push_back(m);
            }
        }
    }

    // heuristic ordering: smaller frontier first
    auto frontier_pop = [&](const Mask& m)->int{
        Mask f;
        m.for_each_bit([&](int cell){ f |= NEI[cell]; });
        Mask frontier = f & (~m);
        return frontier.popcount();
    };
    sort(placements.begin(), placements.end(), [&](const Mask& A, const Mask& B){
        return frontier_pop(A) < frontier_pop(B);
    });

    placements_cache[cache_key] = placements;
    return placements;
}

// ============================================================
// Connectivity check
// ============================================================
static bool connected(const Mask& m){
    if(m.none()) return false;
    int start = -1;
    m.for_each_bit([&](int i){ if(start==-1) start=i; });

    deque<int> q;
    vector<char> vis(NC, 0);
    q.push_back(start);
    vis[start] = 1;

    int seen = 1;
    while(!q.empty()){
        int u=q.front(); q.pop_front();
        Mask nm = NEI[u] & m;
        nm.for_each_bit([&](int v){
            if(!vis[v]){
                vis[v]=1;
                seen++;
                q.push_back(v);
            }
        });
    }
    return seen == m.popcount();
}

// ============================================================
// Backtracking solver
// - Builds 16-omino by connected expansion with a visited-set to kill duplicates
// - Then goes down k=15..1 by remove-one parent-shape relation
// - Memoizes dead BT states by (k, childShapeId, occupiedMask)
// ============================================================

static vector<Mask> chosen(N+1);
static vector<string> chosen_shape_key(N+1);
static Mask occupied;
static vector<int> sumTo(N+1);

// Memo for bt dead states
struct BtState {
    int k;
    int childShapeId;
    uint64_t w[WORDS];
    bool operator==(BtState const& o) const {
        if(k!=o.k || childShapeId!=o.childShapeId) return false;
        for(int i=0;i<WORDS;i++) if(w[i]!=o.w[i]) return false;
        return true;
    }
};
struct BtStateHash {
    size_t operator()(BtState const& s) const noexcept {
        size_t h = std::hash<int>()(s.k) * 1000003u ^ std::hash<int>()(s.childShapeId);
        for(int i=0;i<WORDS;i++){
            uint64_t x = s.w[i];
            h ^= (size_t)x + 0x9e3779b97f4a7c15ULL + (h<<6) + (h>>2);
        }
        return h;
    }
};
static unordered_set<BtState, BtStateHash> dead;

// 16-generator duplicate killer: visited by current mask per size
static vector< unordered_set<Mask,MaskHash> > vis16; // index by size

static bool bt(int k){
    if(k==0) return true;

    // simple capacity pruning
    int freeCells = NC - occupied.popcount();
    if(freeCells < sumTo[k]) return false;

    // memoize dead states for k<N (and also safe for k==N but less useful)
    if(k < N){
        BtState st;
        st.k = k;
        st.childShapeId = get_shape_id(chosen_shape_key[k+1]);
        for(int i=0;i<WORDS;i++) st.w[i] = occupied.w[i];
        if(dead.find(st) != dead.end()) return false;
    }

    if(k==N){
        // Generate connected 16-sets containing REQ[16] and avoiding FIXED_OTHER[16] and occupied.
        Mask required = REQ[N];
        Mask forbidden = FIXED_OTHER[N] | occupied;

        if(required.intersects(forbidden)) return false;
        if(required.popcount() > N) return false;

        vis16.assign(N+1, {});
        for(int s=0;s<=N;s++) vis16[s].reserve(200000);

        vector<Mask> candidates;
        candidates.reserve(200000);

        function<void(Mask, Mask)> dfs = [&](Mask cur, Mask fr){
            int sz = cur.popcount();

            // kill duplicates reached via different growth orders
            auto &vs = vis16[sz];
            if(vs.find(cur) != vs.end()) return;
            vs.insert(cur);

            if(sz == N){
                // already connected by construction (growth via frontier), but keep check for safety
                if(connected(cur)) candidates.push_back(cur);
                return;
            }

            // list frontier cells (order by "neigh into cur", then by index)
            vector<int> fr_cells;
            fr.for_each_bit([&](int i){ fr_cells.push_back(i); });

            auto neigh_into = [&](int cell)->int{
                return (NEI[cell] & cur).popcount();
            };
            sort(fr_cells.begin(), fr_cells.end(), [&](int a, int b){
                int da = neigh_into(a), db = neigh_into(b);
                if(da != db) return da > db;
                return a < b;
            });

            for(int cell: fr_cells){
                Mask nxt = cur;
                nxt.set(cell);

                Mask nxt_fr = fr;
                nxt_fr |= NEI[cell];
                nxt_fr &= ~nxt;
                nxt_fr &= ~forbidden;

                dfs(nxt, nxt_fr);
            }
        };

        Mask fr;
        required.for_each_bit([&](int cell){ fr |= NEI[cell]; });
        fr &= ~required;
        fr &= ~forbidden;

        dfs(required, fr);

        // Heuristic ordering: compact candidates first
        auto frontier_pop = [&](const Mask& m)->int{
            Mask f;
            m.for_each_bit([&](int cell){ f |= NEI[cell]; });
            return (f & (~m)).popcount();
        };
        sort(candidates.begin(), candidates.end(), [&](const Mask& A, const Mask& B){
            return frontier_pop(A) < frontier_pop(B);
        });

        // Uncomment to see whether you’re in “seconds” or “hours” territory:
        cerr << "16-candidates: " << candidates.size() << "\n";

        for(const Mask& m : candidates){
            if(m.intersects(occupied)) continue;

            auto can = canonical_from_mask(m);
            chosen_shape_key[N] = can.key;
            canon_pts_by_key.emplace(can.key, can.canon_pts);

            chosen[N] = m;
            occupied |= m;

            if(bt(N-1)) return true;

            occupied ^= m;
        }
        return false;
    }

    // k < N: parent shapes are remove-one from shape_{k+1}
    unordered_map<string, vector<pair<int,int>>> parent_pts;
    const string& child_key = chosen_shape_key[k+1];
    const auto& child_pts = canon_pts_by_key[child_key];
    auto allowed_keys = parents_by_remove_one(child_pts, parent_pts);

    // ensure stored
    for(auto &kv: parent_pts){
        if(!canon_pts_by_key.count(kv.first)) canon_pts_by_key.emplace(kv.first, kv.second);
    }

    for(const string& skey : allowed_keys){
        auto placements = compute_placements_for_shape(k, skey);
        for(const Mask& m : placements){
            if(m.intersects(occupied)) continue;

            chosen_shape_key[k] = skey;
            chosen[k] = m;
            occupied |= m;

            if(bt(k-1)) return true;

            occupied ^= m;
        }
    }

    if(k < N){
        BtState st;
        st.k = k;
        st.childShapeId = get_shape_id(chosen_shape_key[k+1]);
        for(int i=0;i<WORDS;i++) st.w[i] = occupied.w[i];
        dead.insert(st);
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_neighbors();

    // Build REQ and FIXED_OTHER from givens
    for(auto &e: GIVENS){
        int r=e.first.first, c=e.first.second, v=e.second;
        int cell = id(r,c);
        FIXED_VAL[cell] = v;
        REQ[v].set(cell);
    }
    for(int k=1;k<=N;k++){
        Mask m;
        for(int i=0;i<NC;i++){
            if(FIXED_VAL[i] && FIXED_VAL[i]!=k) m.set(i);
        }
        FIXED_OTHER[k]=m;
    }

    sumTo[0]=0;
    for(int k=1;k<=N;k++) sumTo[k]=sumTo[k-1]+k;

    bool ok = bt(N);
    if(!ok){
        cout << "No solution found.\n";
        return 0;
    }

    auto check_connected_region = [&](int k)->bool{
        return connected(chosen[k]);
    };
    for(int k=1;k<=N;k++){
        if(!check_connected_region(k)){
            cerr << "ERROR: region " << k << " is disconnected!\n";
            return 3;
        }
    }

    // Construct final grid
    vector<vector<int>> grid(H, vector<int>(W, 0));
    for(int k=1;k<=N;k++){
        chosen[k].for_each_bit([&](int cell){
            auto [r,c]=rc(cell);
            grid[r-1][c-1]=k;
        });
    }

    // Verify givens
    for(auto &e: GIVENS){
        int r=e.first.first, c=e.first.second, v=e.second;
        if(grid[r-1][c-1] != v){
            cerr << "Given mismatch at ("<<r<<","<<c<<"): expected "<<v<<" got "<<grid[r-1][c-1]<<"\n";
            return 2;
        }
    }

    cout << "Solved.\n\nGrid ('.' = empty):\n";
    for(int r=0;r<H;r++){
        for(int c=0;c<W;c++){
            if(grid[r][c]==0) cout << " .";
            else cout << setw(2) << grid[r][c];
            if(c+1<W) cout << " ";
        }
        cout << "\n";
    }

    vector<long long> rowS(H,0);
    for(int r=0;r<H;r++){
        long long s=0;
        for(int c=0;c<W;c++) s += grid[r][c];
        rowS[r]=s;
    }
    long long mn = *min_element(rowS.begin(), rowS.end());
    long long mx = *max_element(rowS.begin(), rowS.end());
    long long ans = mn*mx;

    cout << "\nRow sums:\n";
    for(int r=0;r<H;r++){
        cout << "Row " << (r+1) << ": " << rowS[r] << "\n";
    }
    cout << "\nmin row sum = " << mn << "\nmax row sum = " << mx << "\nanswer = " << ans << "\n";
    return 0;
}
