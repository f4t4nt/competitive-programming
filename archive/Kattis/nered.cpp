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
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, rv = 1e18;
    cin >> n >> m;
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
    FOR (i, m) {
        ll x, y;
        cin >> x >> y;
        dp[x][y] = 1;
    }
    FOB (i, 1, n + 1) {
        FOB (j, 1, n + 1) {
            dp[i][j] += dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
        }
    }
    FOB (l, 1, n + 1) {
        FOB (r, l, n + 1) {
            FOB (u, 1, n + 1) {
                FOB (d, u, n + 1) {
                    ll area = (r - l + 1) * (d - u + 1);
                    if (area != m) {
                        continue;
                    }
                    ll cnt = dp[r][d] - dp[l - 1][d] - dp[r][u - 1] + dp[l - 1][u - 1];
                    rv = min(rv, area - cnt);
                }
            }
        }
    }
    cout << rv << '\n';

    return 0;
}