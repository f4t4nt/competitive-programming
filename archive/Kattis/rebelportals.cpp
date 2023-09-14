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

ld dist(vector<ld> &a, vector<ld> &b) {
    return sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1])
        + (a[2] - b[2]) * (a[2] - b[2]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<vector<ld>> ps(n, vector<ld>(3));
    FORE (p, ps) {
        cin >> p[0] >> p[1] >> p[2];
    }
    vector<vector<ld>> d(n, vector<ld>(n));
    FOR (a, n) {
        FOB (b, a + 1, n) {
            d[a][b] = d[b][a] = dist(ps[a], ps[b]);
        }
    }
    // {visited, last, used tp?}
    vector<vector<vector<ld>>> dp(1 << n, vector<vector<ld>>(n, vector<ld>(2, 1e12)));
    dp[0][0][true] = 0;
    FOR (cur, 1 << n) {
        FOR (j, n) {
            FOR (l, n) {
                if (cur & (1 << l)) {
                    ll prev = cur ^ (1 << l);
                    dp[cur][j][true] = min({
                        dp[cur][j][true],
                        dp[prev][l][false],
                        dp[prev][l][true] + d[j][l]
                    });
                    dp[cur][j][false] = min({
                        dp[cur][j][false],
                        dp[prev][l][true] + d[j][l],
                        dp[prev][l][false] + d[j][l]
                    });
                }
            }
        }
    }
    cout << fixed << setprecision(10) << dp.back()[0][true] << '\n';

    return 0;
}