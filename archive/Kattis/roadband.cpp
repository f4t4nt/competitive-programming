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

// imma show YOU how great i am.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ld n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<ld> xs(n + m);
    FORE (x, xs) {
        cin >> x;
    }
    ld base = s * s * (n + m) / 4;
    ssort(xs);
    // dp[i][j], min cost to cover first i points with j means
    vector<vector<ld>> dp(n + m + 1, vector<ld>(k + 1, 1e18));
    dp[0][0] = 0;
    FOB (i, 1, n + m + 1) {
        FOB (j, 1, k + 1) {
            ld sum = 0, sum2 = 0;
            // (x1 - m)^2 + (x2 - m)^2 + ... + (xi - m)^2
            // (x1^2 + x2^2 + ... + xi^2) - 2m(x1 + x2 + ... + xi) + i * m^2
            FORR (l, i) {
                sum += xs[l];
                sum2 += xs[l] * xs[l];
                ld avg = sum / (i - l);
                dp[i][j] = min(dp[i][j], dp[l][j - 1] + sum2 - 2 * avg * sum + (i - l) * avg * avg);
            }
        }
    }
    cout << fixed << setprecision(10) << base + dp[n + m][k] << '\n';

    return 0;
}