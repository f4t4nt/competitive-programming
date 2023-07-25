#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

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

constexpr ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n);
    // [state][last] = number of ways to get to state with last without repeating
    vector<vector<ll>> dp(1 << n, vector<ll>(n));
    FOR (i, m) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
    }
    dp[1][0] = 1;
    FOR (state, 1 << n) {
        FOR (last, n) {
            if (dp[state][last] == 0) {
                continue;
            }
            FORE (next, adj[last]) {
                if (state & (1 << next)) {
                    continue;
                }
                dp[state | (1 << next)][next] += dp[state][last];
                dp[state | (1 << next)][next] %= MOD;
            }
        }
    }
    ll rv = dp[(1 << n) - 1][n - 1];
    cout << rv << '\n';

    return 0;
}