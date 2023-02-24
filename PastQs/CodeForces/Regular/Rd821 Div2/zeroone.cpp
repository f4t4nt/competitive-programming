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

ll eval(ll l, ll r, ll &x, ll &y) {
    if (l + 1 == r) {
        return min(x, 2 * y);
    } else {
        return min((r - l) * x, y);
    }
}

ll dfs(ll l, ll r, ll &x, ll &y, vector<ll> &ref, vector<vector<ll>> &dp) {
    if (l >= r) {
        return 0;
    } elif (dp[l][r] != 1e18) {
        return dp[l][r];
    } else {
        dp[l][r] = dfs(l, r - 2, x, y, ref, dp) + eval(ref[r - 1], ref[r], x, y);
        dp[l][r] = min(dp[l][r], dfs(l + 1, r - 1, x, y, ref, dp) + eval(ref[l], ref[r], x, y));
        dp[l][r] = min(dp[l][r], dfs(l + 2, r, x, y, ref, dp) + eval(ref[l], ref[l + 1], x, y));
        return dp[l][r];
    }
}

int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll n, x, y;
        cin >> n >> x >> y;
        vector<ll> a(n), b(n), c(n), ref;
        FOR(i, n) {
            char tmp;
            cin >> tmp;
            a[i] = tmp - '0';
        }
        FOR(i, n) {
            char tmp;
            cin >> tmp;
            b[i] = tmp - '0';
        }
        FOR(i, n) {
            c[i] = a[i] ^ b[i];
            if (c[i] == 1) {
                ref.pb(i);
            }
        }
        if (ref.size() % 2 == 1) {
            cout << "-1\n";
            continue;
        }
        if (x >= y) {
            if (ref.size() == 2) {
                if (abs(ref[0] - ref[1]) == 1) {
                    cout << min(x, 2 * y) << '\n';
                } else {
                    cout << y << '\n';
                }
            } else {
                cout << ref.size() / 2 * y << '\n';
            }
        } else {
            vector<vector<ll>> dp(sz(ref), vector<ll>(sz(ref), 1e18));
            cout << dfs(0, sz(ref) - 1, x, y, ref, dp) << '\n';
        }
    }
    return 0;
}