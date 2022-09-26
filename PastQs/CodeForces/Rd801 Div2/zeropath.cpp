#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

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

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
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
    ll t;
    cin >> t;
    while(t--) {
        ll n, m;
        cin >> n >> m;
        vector<vector<ll>> a(n, vector<ll>(m));
        FOR(i, n) FOR(j, m) {
            cin >> a[i][j];
            if(a[i][j] == -1) a[i][j] = 0;
        }
        ll x = n + m - 1;
        if(x % 2 == 1) {
            cout << "NO\n";
            continue;
        }
        x /= 2;
        vector<vector<pair<ll,ll>>> dp(n, vector<pair<ll,ll>>(m, {1e18, -1e18}));
        dp[0][0] = {a[0][0], a[0][0]};
        FOR(i, n) {
            FOR(j, m) {
                if(i > 0) {
                    dp[i][j].first = min(dp[i][j].first, a[i][j] + dp[i - 1][j].first);
                    dp[i][j].second = max(dp[i][j].second, a[i][j] + dp[i - 1][j].second);
                }
                if(j > 0) {
                    dp[i][j].first = min(dp[i][j].first, a[i][j] + dp[i][j - 1].first);
                    dp[i][j].second = max(dp[i][j].second, a[i][j] + dp[i][j - 1].second);
                }
            }
        }
        if(dp[n - 1][m - 1].first <= x && dp[n - 1][m - 1].second >= x) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}