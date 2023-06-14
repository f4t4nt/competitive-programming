#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

    while (true) {
        ll k, n, e;
        cin >> k >> n >> e;
        ll pow2n = 1 << n;
        if (k == 0 && n == 0 && e == 0) {
            break;
        }
        vector<vector<ll>> adj(pow2n, vector<ll>());
        FOR (i, e) {
            ll u, v;
            cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vector<vector<ld>> dp(k, vector<ld>(pow2n));
        dp[0] = vector<ld>(pow2n, 1 / (ld) pow2n);
        FOR (i, k - 1) {
            FOR (u,pow2n) {
                FORE (v, adj[u]) {
                    dp[i + 1][v] += dp[i][u] / (ld) sz(adj[u]);
                }
            }
        }
        vector<vector<ld>> ref(k, vector<ld>(n));
        FOR (u, pow2n) {
            FOR (i, n) {
                if (u & (1 << i)) {
                    FOR (j, k) {
                        ref[j][i] += dp[j][u];
                    }
                }
            }
        }
        bool ok = true;
        FOR (i, n) {
            FOR (j, k) {
                ok &= (ref[j][i] > 0.25 && ref[j][i] < 0.75);
            }
        }
        cout << (ok ? "Yes" : "No") << '\n';
    }

    return 0;
}