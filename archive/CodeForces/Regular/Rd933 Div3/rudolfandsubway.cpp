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
    pld,
    null_type,
    less<pld>,
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
#define f first
#define s second

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    // cout << 1 << '\n';
    // cout << 200000 << ' ' << 200000 << '\n';
    // FOB (i, 2, 200001) cout << i - 1 << ' ' << i << ' ' << i << '\n';
    // cout << 2 << ' ' << 3 << '\n';

    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        vector<map<ll, vector<ll>>> adj(n);
        FOR (i, m) {
            ll u, v, c; cin >> u >> v >> c; u--, v--;
            adj[u][c].pb(v);
            adj[v][c].pb(u);
        }
        ll b, e; cin >> b >> e; b--, e--;
        map<pll, ll> dist;
        deque<tuple<ll, ll, ll>> q;
        // q.pb({b, 0, 0});
        // while (!q.empty()) {
        //     auto [u, c, d] = q.front(); q.pop_front();
        //     if (dist.count({u, c})) continue;
        //     dist[{u, c}] = d;
        //     if (c == 0) {
        //         FORE (v, adj[u]) q.pb({u, v.f, d + 1});
        //     } else {
        //         q.push_front({u, 0, d});
        //         FORE (v, adj[u][c]) q.pb({v, c, d});
        //     }
        // }
        q.pb({0, b, 0});
        while (!q.empty()) {
            auto [d, x, a] = q.front(); q.pop_front();
            if (dist.count({x, a})) continue;
            dist[{x, a}] = d;
            if (a) {
                q.push_front({d, x, 0});
                FORE (y, adj[x][a]) q.push_front({d, y, a});
            } else {
                FORE (v, adj[x]) q.pb({d + 1, x, v.f});
            }
        }
        // q.emplace_back(0, b, 0);
        // while (!q.empty()) {
        //     auto [d, x, a] = q.front();
        //     q.pop_front();
            
        //     if (dist.count({x, a})) {
        //         continue;
        //     }
        //     dist[{x, a}] = d;
            
        //     if (a) {
        //         q.emplace_front(d, x, 0);
        //         for (auto y : adj[x][a]) {
        //             q.emplace_front(d, y, a);
        //         }
        //     } else {
        //         for (auto &[a, _] : adj[x]) {
        //             q.emplace_back(d + 1, x, a);
        //         }
        //     }
        // }
        cout << dist[{e, 0}] << '\n';
    }

    return 0;
}