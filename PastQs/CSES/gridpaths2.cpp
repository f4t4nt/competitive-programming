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
#define mp make_pair
#define mt make_tuple
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

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

constexpr ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<str> grid(n);
    FOR (i, n) {
        cin >> grid[i];
    }

    if (grid[0][0] == '*' || grid[n - 1][n - 1] == '*') {
        cout << 0 << '\n';
        return 0;
    }

    vector<vector<ll>> dp(n, vector<ll>(n));
    dp[0][0] = 1;

    FOR (i, n) {
        FOR (j, n) {
            if (i > 0) {
                if (grid[i - 1][j] == '.') {
                    dp[i][j] += dp[i - 1][j];
                }
            }
            if (j > 0) {
                if (grid[i][j - 1] == '.') {
                    dp[i][j] += dp[i][j - 1];
                }
            }
            dp[i][j] %= MOD;
        }
    }

    cout << dp[n - 1][n - 1] << '\n';

    return 0;
}