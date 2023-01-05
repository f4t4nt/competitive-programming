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
#include <string.h>
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

bool valid(ll &mid, ll &n, ll &m, vector<vector<ll>> &a) {
    vector<vector<ll>> dp(n, vector<ll>(m));
    FOR (i, n) {
        dp[i][0] = a[i][0] >= mid;
        if (dp[i][0] >= mid) {
            return true;
        }
    }
    FOR (j, m) {
        dp[0][j] = a[0][j] >= mid;
        if (dp[0][j] >= mid) {
            return true;
        }
    }
    FOB (i, 1, n) {
        FOB (j, 1, m) {
            if (a[i][j] >= mid) {
                dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                if (dp[i][j] >= mid) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll n, m;
        cin >> n >> m;
        vector<vector<ll>> a(n, vector<ll>(m));
        FOR (i, n) {
            FOR (j, m) {
                cin >> a[i][j];
            }
        }
        ll lo = 0, hi = min(n, m);
        while (lo < hi) {
            ll mid = (lo + hi + 1) / 2;
            if (valid(mid, n, m, a)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        cout << lo << '\n';
    }
    return 0;
}