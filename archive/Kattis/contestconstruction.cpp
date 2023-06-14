#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<ll> d(n + 2);
    FOR (i, n) {
        cin >> d[i];
    }
    ssort(d);
    d[0] = 1e18;
    d[1] = 1e18;

    // dp[i][j][k] indicates
    // # of elements is i
    // last element is j
    // 2nd last element is k
    vector<vector<vector<ll>>> dp(m + 1, vector<vector<ll>>(n + 2, vector<ll>(n + 2, 0)));
    dp[0][1][0] = 1;
    FOB (i, 1, m + 1) {
        FOR (j, n + 2) {
            FOR (k, j) {
                FOB (l, j + 1, n + 2) {
                    if (d[j] + d[k] < d[l]) {
                        break;
                    }
                    dp[i][l][j] += dp[i - 1][j][k];
                }
            }
        }
    }

    ll rv = 0;
    FOR (i, n + 2) {
        FOR (j, n + 2) {
            rv += dp[m][i][j];
        }
    }
    cout << rv << '\n';

    return 0;
}