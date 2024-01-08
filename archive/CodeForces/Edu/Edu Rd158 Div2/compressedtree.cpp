#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n, rv = 0;
        cin >> n;
        vector<ll> a(n), dp(n);
        FOR (i, n) {
            cin >> a[i];
        }
        vector<vector<ll>> adj(n);
        FOR (i, n - 1) {
            ll u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        auto dfs = [&](auto &&f, ll u, ll p) -> void {
            vector<ll> dps;
            FORE (v, adj[u]) {
                if (v != p) {
                    f(f, v, u);
                    dps.pb(dp[v]);
                }
            }
            rsort(dps);
            dp[u] = a[u];
            rv = max(rv, a[u]);
            if (sz(dps) > 0) {
                dp[u] = max(dp[u], dps[0]);
                rv = max(rv, dps[0] + a[u]);
                if (sz(dps) > 1) {
                    dp[u] = max(dp[u], dps[0] + dps[1] + a[u]);
                    rv = max(rv, dps[0] + dps[1]);
                    if (sz(dps) > 2) {
                        ll sum = dps[0] + dps[1] + dps[2];
                        FOB (i, 3, sz(dps)) {
                            if (dps[i] > 0) {
                                sum += dps[i];
                            }
                        }
                        dp[u] = max(dp[u], sum + a[u]);
                        rv = max(rv, sum + a[u]);
                    }
                }
            }
        };
        dfs(dfs, 0, -1);
        cout << rv << '\n';
    }

    return 0;
}