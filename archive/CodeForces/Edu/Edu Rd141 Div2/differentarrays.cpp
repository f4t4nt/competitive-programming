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

constexpr ll MOD = 998244353;

int main() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    FOR (i, n) {
        cin >> a[i];
    }
    vector<ll> dp0(180001, 0);
    dp0[a[1] + 90000] = 1;
    FOB (i, 2, n) {
        vector<ll> dp1(180001, 0);
        FOR (j, 180001) {
            if (j != 90000) {
                if (abs(a[i] - (j - 90000)) >= 90000) {
                    dp1[180000] = (dp1[180000] + dp0[j]) % MOD;
                } else {
                    dp1[a[i] - (j - 90000) + 90000] = (dp1[a[i] - (j - 90000) + 90000] + dp0[j]) % MOD;
                }
                if (abs(a[i] + (j - 90000)) >= 90000) {
                    dp1[180000] = (dp1[180000] + dp0[j]) % MOD;
                } else {
                    dp1[a[i] + (j - 90000) + 90000] = (dp1[a[i] + (j - 90000) + 90000] + dp0[j]) % MOD;
                }
            } else {
                if (abs(a[i]) >= 90000) {
                    dp1[180000] = (dp1[180000] + dp0[j]) % MOD;
                } else {
                    dp1[a[i] + 90000] = (dp1[a[i] + 90000] + dp0[j]) % MOD;
                }
            }
        }
        dp0 = dp1;
    }
    ll rv = 0;
    FORE (x, dp0) {
        rv = (rv + x) % MOD;
    }
    cout << rv << '\n';
    return 0;
}