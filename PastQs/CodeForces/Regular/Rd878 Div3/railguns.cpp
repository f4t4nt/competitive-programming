#include <bits/stdc++.h>
    
using namespace std;
    
using ll = long long;
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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

void view(vector<vector<vector<bool>>> &states, ll &n, ll &m, ll &r) {
    FOR (t, r + 1) {
        cout << "t = " << t << '\n';
        FOR (i, n + 1) {
            FOR (j, m + 1) {
                cout << (states[i][j][t] ? '#' : ' ');
            }
            cout << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n, m, r;
        cin >> n >> m >> r;
        vector<vector<vector<bool>>> open(n + 1,
            vector<vector<bool>>(m + 1,
            vector<bool>(r + 1,
            true))),
            dp = open;
        FOR (i, r) {
            ll r_t, r_axis, r_pos;
            cin >> r_t >> r_axis >> r_pos;
            if (r_axis == 1) {
                FOR (j, m + 1) {
                    if (0 <= r_t - r_pos - j && r_t - r_pos - j <= r) {
                        open[r_pos][j][r_t - r_pos - j] = false;
                    }
                }
            } else {
                FOR (j, n + 1) {
                    if (0 <= r_t - r_pos - j && r_t - r_pos - j <= r) {
                        open[j][r_pos][r_t - r_pos - j] = false;
                    }
                }
            }
        }
        FOR (i, n + 1) {
            FOR (j, m + 1) {
                FOR (k, r + 1) {
                    dp[i][j][k] = !i && !j && !k;
                    if (open[i][j][k] && ((i && dp[i - 1][j][k]) || (j && dp[i][j - 1][k]) || (k && dp[i][j][k - 1]))) {
                        dp[i][j][k] = true;
                    }
                }
            }
        }
        ll rv = -1;
        FOR (k, r + 1) {
            if (dp[n][m][k]) {
                rv = n + m + k;
                break;
            }
        }
        cout << rv << '\n';
    }

    return 0;
}