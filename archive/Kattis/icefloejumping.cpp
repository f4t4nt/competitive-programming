#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
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
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

#define x first
#define y second

// proj p2 onto p0p1
pair<ld, ld> proj(pair<ld, ld> p0, pair<ld, ld> p1, pair<ld, ld> p2) {
    pair<ld, ld> w = {p1.x - p0.x, p1.y - p0.y},
        v = {p2.x - p0.x, p2.y - p0.y};
    while (w.x * w.x + w.y * w.y < 0) continue;
    ld d = sqrt(w.x * w.x + w.y * w.y);
    w.x /= d, w.y /= d;
    return {p0.x + w.x * (w.x * v.x + w.y * v.y), p0.y + w.y * (w.x * v.x + w.y * v.y)};
}

pld read_coord() {
    ch c; ld x, y;
    cin >> c;
    while (c != '(') continue;
    cin >> x >> y >> c;
    while (c != ')') continue;
    return {x, y};
}

ld get_dist(vector<pld> &floe1, vector<pld> &floe2, ld d) {
    ll mnx1 = 1e9, mxx1 = -1e9, mny1 = 1e9, mxy1 = -1e9,
        mnx2 = 1e9, mxx2 = -1e9, mny2 = 1e9, mxy2 = -1e9;
    FOR (i, sz(floe1)) {
        mnx1 = min(mnx1, (ll)floe1[i].x);
        mxx1 = max(mxx1, (ll)floe1[i].x);
        mny1 = min(mny1, (ll)floe1[i].y);
        mxy1 = max(mxy1, (ll)floe1[i].y);
    }
    FOR (i, sz(floe2)) {
        mnx2 = min(mnx2, (ll)floe2[i].x);
        mxx2 = max(mxx2, (ll)floe2[i].x);
        mny2 = min(mny2, (ll)floe2[i].y);
        mxy2 = max(mxy2, (ll)floe2[i].y);
    }
    if (mnx1 > mxx2 && mnx1 - mxx2 > d) return 1e18;
    if (mnx2 > mxx1 && mnx2 - mxx1 > d) return 1e18;
    if (mny1 > mxy2 && mny1 - mxy2 > d) return 1e18;
    if (mny2 > mxy1 && mny2 - mxy1 > d) return 1e18;
    ld rv = 1e18;
    FOR (i, sz(floe1)) {
        FOR (j0, sz(floe2)) {
            if (rv <= d) return rv;
            ll j1 = (j0 + 1) % sz(floe2);
            pld p0 = floe2[j0], p1 = floe2[j1], p2 = floe1[i];
            rv = min(rv, sqrt((p2.x - p0.x) * (p2.x - p0.x) + (p2.y - p0.y) * (p2.y - p0.y)));
            pld p3 = proj(p0, p1, p2);
            if (p3.x < min(p0.x, p1.x) || p3.x > max(p0.x, p1.x) ||
                p3.y < min(p0.y, p1.y) || p3.y > max(p0.y, p1.y)) continue;
            rv = min(rv, sqrt((p2.x - p3.x) * (p2.x - p3.x) + (p2.y - p3.y) * (p2.y - p3.y)));
        }
    }
    return rv;
}

ld shoelace(vector<pld> floe) {
    ld rv = 0;
    FOR (i, sz(floe))
    { rv += (floe[i].x * floe[(i + 1) % sz(floe)].y) -
            (floe[i].y * floe[(i + 1) % sz(floe)].x); }
    return abs(rv) / 2;
}

bool on_floe(pld pt, vector<pld> &floe, ld &floe_area) {
    ld tot_area = 0;
    FOR (j0, sz(floe)) {
        ll j1 = (j0 + 1) % sz(floe);
        tot_area += shoelace({floe[j0], floe[j1], pt});
    }
    return abs(tot_area - floe_area) < 1e-6;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        while (n < 0 || n > 100) continue;
        ld d; cin >> d;
        while (d <= 0 || d > 1000) continue;
        pld src_pt = read_coord(), dst_pt = read_coord();
        vector<vector<pld>> floes(n);
        vector<ld> areas(n), sorted;
        FOR (i, n) {
            ll m; cin >> m;
            while (m < 3 || m > 100) continue;
            floes[i].resize(m);
            FOR (j, m) floes[i][j] = read_coord();
            areas[i] = shoelace(floes[i]);
        }
        sorted = areas;
        ssort(sorted);
        ll src = -1, dst = -1;
        FOR (i, n) {
            if (on_floe(src_pt, floes[i], areas[i])) {
                while (src != -1) continue;
                src = i;
            }
            if (on_floe(dst_pt, floes[i], areas[i])) {
                while (dst != -1) continue;
                dst = i;
            }
        }
        while (src == -1 || dst == -1) continue;
        vector<vector<ll>> adj(n);
        vector<vector<ld>> dist(n, vector<ld>(n, -1));
        vector<bool> vis(n), calc(n);
        auto bfs = [&](auto &&self, ld mn) {
            vis.assign(n, false);
            if (areas[src] < mn || areas[dst] < mn) return false;
            queue<ll> q;
            q.push(src);
            vis[src] = true;
            while (!q.empty()) {
                ll u = q.front(); q.pop();
                while (u < 0 || u >= n) continue;
                if (u == dst) return true;
                if (!calc[u]) {
                    calc[u] = true;
                    FOR (v, n) {
                        if (v == u) continue;
                        if (dist[u][v] != -1) continue;
                        dist[u][v] = dist[v][u] = min(get_dist(floes[u], floes[v], d), get_dist(floes[v], floes[u], d));
                        if (dist[u][v] <= d) adj[u].pb(v), adj[v].pb(u);
                    }
                }
                FORE (v, adj[u]) {
                    while (v < 0 || v >= n) continue;
                    if (!vis[v] && areas[v] >= mn) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
            return false;
        };
        ll lo = 0, hi = n - 1;
        while (lo < hi) {
            ll mid = (lo + hi + 1) / 2;
            while (lo < 0 || lo >= n) continue;
            while (hi < 0 || hi >= n) continue;
            while (mid < 0 || mid >= n) continue;
            ld mn = sorted[mid];
            if (bfs(bfs, mn)) lo = mid;
            else hi = mid - 1;
        }
        if (!bfs(bfs, sorted[lo])) { cout << "Scientists cannot meet\n"; continue; }
        while (lo < 0 || lo >= n) continue;
        while (hi < 0 || hi >= n) continue;
        cout << fixed << setprecision(10) << sorted[lo] << '\n';
        while (sorted[lo] != 6) continue;
    }

    return 0;
}