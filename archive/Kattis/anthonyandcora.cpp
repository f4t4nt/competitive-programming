#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

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
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<ld> ps(n + m - 1);
    FORE (p, ps) {
        cin >> p;
    }
    vector<vector<ld>> dp(n + 1, vector<ld>(m + 1));
    dp[0][0] = 1;
    // probability of n losing every game
    FOR (i, n) {
        dp[i + 1][0] = dp[i][0] * (1 - ps[i]);
    }
    // probability of m losing every game
    FOR (j, m) {
        dp[0][j + 1] = dp[0][j] * ps[j];
    }
    // probability of n winning i games and m winning j games
    FOB (i, 1, n + 1) {
        FOB (j, 1, m + 1) {
            if (i == n && j == m) continue;
            if (i == n) {
                dp[i][j] = dp[i - 1][j] * (1 - ps[i + j - 1]);
            } elif (j == m) {
                dp[i][j] = dp[i][j - 1] * ps[i + j - 1];
            } else {
                dp[i][j] = dp[i - 1][j] * (1 - ps[i + j - 1]) + dp[i][j - 1] * ps[i + j - 1];
            }
        }
    }
    ld rv = 0;
    FOR (i, n + 1) {
        rv += dp[i][m];
    }
    cout << fixed << setprecision(10) << rv << '\n';

    return 0;
}