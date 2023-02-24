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
    ll t;
    cin >> t;
    vector<ll> inv(2e5 + 5);
    inv[1] = 1;
    FOB(i, 2, 2e5 + 5) {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
    }
    FORE(x, inv) {
        x = (x * x) % MOD;
    }
    while (t--) {
        ll n, zeros = 0, ones = 0;
        cin >> n;
        ll m = (n * (n - 1) / 2) % MOD;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
            if (a[i] == 0) {
                zeros++;
            }
        }
        FOR (i, zeros) {
            if (a[i] == 1) {
                ones++;
            }
        }
        ll rv = 0;
        FOR (i, ones + 1) {
            rv = (rv + inv[i]) % MOD;
        }
        rv = (rv * m) % MOD;
        cout << rv << '\n';
    }
    return 0;
}