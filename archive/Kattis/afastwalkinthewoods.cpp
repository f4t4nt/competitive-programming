#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FORE(x, C) for(auto &x : C)
 
#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

map<ch, ll> dir_mp = {
    {'N', 0},
    {'W', 1},
    {'S', 2},
    {'E', 3}
};

void trav_edge(
    ll e, ll &cur,
    vector<vector<ll>> &adj,
    vector<tuple<ll, ll, ll, ll>> &edges,
    vector<ll> &stk,
    vector<ll> &vis,
    ll &loop,
    ll reps = 1,
    bool dbg = false
) {
    assert(e != -1);
    assert(get<0>(edges[e]) == cur);
    ll nxt = get<1>(edges[e]);
    get<2>(edges[e]) -= reps;
    get<2>(edges[e ^ 1]) -= reps;
    assert(get<2>(edges[e]) >= 0);
    assert(get<2>(edges[e]) == get<2>(edges[e ^ 1]));
    if (get<2>(edges[e]) == 0) {
        FOR (i, 4) if (adj[cur][i] == e) adj[cur][i] = -1;
        FOR (i, 4) if (adj[nxt][i] == (e ^ 1)) adj[nxt][i] = -1;
        vis.assign(sz(edges), -1);
        stk.clear();
    } else {
        loop = vis[e];
        vis[e] = sz(stk);
        stk.pb(e);
    }
    cur = nxt;
    if (dbg) {
        if (reps != 1) cerr << "reps: " << reps << endl;
        cerr << get<0>(edges[e]) << " -> " << get<1>(edges[e]) << ", " << get<2>(edges[e]) << endl;
        cerr << "edges: " << endl;
        for (ll e = 0; e < edges.size(); e += 2) {
            auto [u, v, w, vd] = edges[e];
            cerr << u << ' ' << v << ' ' << w << endl;
        }
        cerr << "stk: ";
        FORE (e, stk) cerr << get<0>(edges[e]) << " -> " << get<1>(edges[e]) << ", ";
        cerr << endl << endl;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<pair<ll, ll>> pts(n);
    // <from, to, weight, dir>
    vector<tuple<ll, ll, ll, ll>> edges(2 * m);
    vector<vector<ll>> adj(n, vector<ll>(4, -1));
    FOR (i, n) cin >> pts[i].first >> pts[i].second;
    FOR (i, m) {
        ll u, v, w, vd, ud;
        cin >> u >> v >> w;
        u--, v--;
        if (pts[u] > pts[v]) swap(u, v);
        // u is west of v
        if (pts[u].first < pts[v].first) {
            assert(pts[u].second == pts[v].second);
            vd = 1, ud = 3;
            adj[u][ud] = 2 * i + 1;
            adj[v][vd] = 2 * i;
        // u is south of v
        } elif (pts[u].second < pts[v].second) {
            assert(pts[u].first == pts[v].first);
            vd = 2, ud = 0;
            adj[u][ud] = 2 * i + 1;
            adj[v][vd] = 2 * i;
        } else assert(false);
        edges[2 * i] = {v, u, w, vd};
        edges[2 * i + 1] = {u, v, w, ud};
    }
    ll cur, dir, loop = -1;
    ch dir0;
    cin >> cur >> dir0;
    cur--, dir = dir_mp[dir0];
    vector<ll> stk, vis(sz(edges), -1);
    trav_edge(adj[cur][dir], cur, adj, edges, stk, vis, loop);
    while (true) {
        ll nxt = -1;
        set<ll> nxt_dirs;
        FOR (i, 4) if (adj[cur][i] != -1) nxt_dirs.insert(i);
        nxt_dirs.erase(dir ^ 2);
        if (sz(nxt_dirs) == 0) break;
        elif (sz(nxt_dirs) == 1) dir = *nxt_dirs.begin();
        elif (sz(nxt_dirs) == 2) {
            dir ^= 2;
            while (!nxt_dirs.count(dir)) dir = (dir + 3) % 4;
        } else assert(sz(nxt_dirs) == 3);
        trav_edge(adj[cur][dir], cur, adj, edges, stk, vis, loop);
        if (loop != -1) {
            // cerr << "loop: " << loop << endl << endl;
            ll reps = LLONG_MAX;
            map<ll, ll> cnts;
            FOB (i, loop + 1, sz(stk)) cnts[stk[i] / 2]++;
            FOB (i, loop + 1, sz(stk)) {
                auto [u, v, w, vd] = edges[stk[i]];
                reps = min(reps, w / cnts[stk[i] / 2]);
            }
            ll prev_sz = sz(stk);
            FOB (i, loop + 1, prev_sz) trav_edge(stk[i], cur, adj, edges, stk, vis, loop, reps);
        }
    }
    cout << pts[cur].first << ' ' << pts[cur].second << '\n';

    return 0;
}