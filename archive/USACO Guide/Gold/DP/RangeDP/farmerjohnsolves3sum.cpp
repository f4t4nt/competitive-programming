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

// http://www.usaco.org/index.php?page=viewproblem2&cpid=994

int main() {
    ifstream cin("threesum.in");
    ofstream cout("threesum.out");
    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    FOR(i, n) {
        cin >> a[i];
    }
    vector<vector<ll>> dp(n, vector<ll>(n));
    vector<ll> ref(2e6 + 1);
    FOR(i, n) {
        FOB(j, i + 1, n) {
            if (-a[i] - a[j] + 1e6 >= 0 && -a[i] - a[j] + 1e6 <= 2e6) {
                dp[i][j] = ref[-a[i] - a[j] + 1e6];
            }
            ref[a[j] + 1e6]++;
        }
        FOB(j, i + 1, n) {
            ref[a[j] + 1e6]--;
        }
    }
    FOB(len, 2, n) {
        FOR(i, n - len) {
            ll j = i + len;
            dp[i][j] += dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1];
        }
    }
    FOR(i, q) {
        ll l, r;
        cin >> l >> r;
        l--;
        r--;
        cout << dp[l][r] << '\n';
    }
    return 0;
}