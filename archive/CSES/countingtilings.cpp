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

constexpr ll MOD = 1e9 + 7;

vector<ll> count(ll &x, ll &n) {
    set<vector<ll>> dp0 = {{}};
    ll horizontal = 3, vertical = 1;
    vector<ll> nv;
    FOR (i, n) {
        set<vector<ll>> dp1;
        FORE (v, dp0) {
            if (sz(v) > i) {
                dp1.insert(v);
                continue;
            }
            if ((x & vertical) == vertical) {
                nv = v;
                nv.pb(1);
                dp1.insert(nv);
                if ((x & horizontal) == horizontal) {
                    nv = v;
                    nv.pb(2), nv.pb(2);
                    dp1.insert(nv);
                }
            } else {
                nv = v;
                nv.pb(0);
                dp1.insert(nv);
            }
        }

        dp0 = dp1;
        horizontal <<= 1, vertical <<= 1;
    }

    vector<ll> rv;
    FORE (v, dp0) {
        ll res = 0;
        FOR (i, n) {
            res |= (v[i] % 2) << i;
        }

        rv.pb(res);
    }

    return rv;
}

int main() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> molds(1 << n);
    FOR (i, 1 << n) {
        molds[i] = count(i, n);
    } 
    vector<vector<ll>> dp(m, vector<ll>(1 << n));
    FORE (mold, molds) {
        bool valid = false;
        FORE (v, mold) {
            if (v == 0) {
                valid = true;
                break;
            }
        }
        dp[0][mold[0]] += valid;
    }

    FOB (i, 1, m) {
        FOR (j, 1 << n) {
            FORE (mold, molds[j]) {
                ll mold_inv = mold ^ ((1 << n) - 1);
                dp[i][j] += dp[i - 1][mold_inv];
                dp[i][j] %= MOD;
            }
        }
    }

    cout << dp[m - 1][(1 << n) - 1] << '\n';
    return 0;
}