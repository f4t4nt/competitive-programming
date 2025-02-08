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
    ll,
    null_type,
    less<ll>,
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
#define x first
#define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

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

    ll n, m, q; cin >> n >> m >> q;
    vector<tuple<ll, ll, ll>> pts(n);
    for (auto &[x, y, z] : pts) cin >> x >> y >> z;
    vector<vector<pair<ll, ld>>> adj(n);
    FOR (i, m) {
        ll u, v; cin >> u >> v;
        u--, v--;
        auto [ux, uy, uz] = pts[u];
        auto [vx, vy, vz] = pts[v];
        ld dx = ux - vx,
            dy = uy - vy,
            dz = uz - vz;
        ld w = sqrt(sqrt(dx * dx + dy * dy + dz * dz));
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    vector<ld> dist(n, 1e18);
    std::priority_queue<pair<ld, ll>, vector<pair<ld, ll>>, greater<>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    while (q--) {
        ll tgt; cin >> tgt; tgt--;
        ld t; cin >> t;
        t /= dist[tgt];
        ld c = (t - sqrt(t * t - 4)) / 2;
        if (c > 2 || t < 2) cout << "impossible\n";
        else cout << fixed<< setprecision(10) << 2 * c * dist[tgt] << '\n';
    }

    return 0;
}