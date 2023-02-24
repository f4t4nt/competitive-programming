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

// https://codingcompetitions.withgoogle.com/codejam/round/000000000087711b/0000000000accfdb

int main() {
    ll t;
    cin >> t;
    FOR(i, t) {
        ll n, p;
        cin >> n >> p;
        vector<vector<ll>> x(n, vector<ll>(p));
        vector<pair<ll, ll>> ref(n + 1, { 1e18, -1e18 }), dp(n + 1);
        ref[0] = { 0, 0 };
        FOR(i, n) {
            FOR(j, p) {
                cin >> x[i][j];
                ref[i + 1].first = min(ref[i + 1].first, x[i][j]);
                ref[i + 1].second = max(ref[i + 1].second, x[i][j]);
            }
        }
        FOR(i, n) {
            dp[i + 1] = { ref[i + 1].second - ref[i + 1].first + min(abs(ref[i + 1].second - ref[i].first) + dp[i].first,
                                                                    abs(ref[i + 1].second - ref[i].second) + dp[i].second), 
                          ref[i + 1].second - ref[i + 1].first + min(abs(ref[i + 1].first - ref[i].first) + dp[i].first,
                                                                    abs(ref[i + 1].first - ref[i].second) + dp[i].second) };
        }
        cout << "Case #" << i + 1 << ": " << min(dp[n].first, dp[n].second) << '\n';
    }
    return 0;
}