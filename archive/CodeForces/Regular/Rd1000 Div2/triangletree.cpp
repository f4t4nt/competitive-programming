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
// #define x first
// #define y second

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

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        if (n == 1) {
            cout << 0 << '\n';
            continue;
        }
        vector<ll> depth(n + 1), subsz(n + 1), parent(n + 1);
        vector<vector<ll>> adj(n + 1), children(n + 1);
        FOR (i, n - 1) {
            ll u, v; cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        auto dfs = [&](auto &&self, ll u, ll p) -> void {
            parent[u] = p;
            subsz[u] = 1;
            for (ll v : adj[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                children[u].pb(v);
                self(self, v, u);
                subsz[u] += subsz[v];
            }
        };
        depth[1] = 0;
        dfs(dfs, 1, 0);
        ll sum_depth = 0;
        vector<ll> all_depths(n);
        FOR1 (i, n + 1) {
            sum_depth += depth[i];
            all_depths[i - 1] = depth[i];
        }
        ssort(all_depths);
        ll sum_min_all_pairs = 0;
        FOR (i, n) {
            ll dval = all_depths[i];
            ll count_right = n - 1 - i;
            if (count_right <= 0) break;
            sum_min_all_pairs += dval * count_right;
        }
        ll sum_lca_all = 0;
        FOR1 (x, n + 1) {
            ll s = subsz[x] - 1;
            if (s <= 0) continue;
            ll q = 0;
            for (ll c : children[x]) {
                ll sc = subsz[c];
                q += sc * sc;
            }
            ll pair_count = (s * s - q) / 2;
            ll cx = s + pair_count;
            sum_lca_all += depth[x] * cx;
        }
        ll nc2 = n * (n - 1) / 2;
        ll ans = 2 * sum_min_all_pairs - 2 * sum_lca_all - nc2 + sum_depth;
        cout << ans << '\n';
    }

    return 0;
}