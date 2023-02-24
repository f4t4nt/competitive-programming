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

ll fact[3000005], inv[3000005];

ll choose(ll n, ll k, ll MOD) {
    return (((fact[n] * inv[k]) % MOD) * inv[n - k]) % MOD;
}

ll pow(ll n, ll m, ll MOD) {
    ll res = 1;
    while (m) {
        if (m & 1) {
            res = (res * n) % MOD;
        }
        n = (n * n) % MOD;
        m >>= 1;
    }
    return res;
}

int main() {
    ll n, MOD;
    cin >> n >> MOD;
    fact[0] = 1;
    FOB (i, 1, 3 * n + 1) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    inv[3 * n] = pow(fact[3 * n], MOD - 2, MOD);
    FORR (i, 3 * n) {
        inv[i] = (inv[i + 1] * (i + 1)) % MOD;
    }
    vector<ll> ref(4);

    ref[0] = 1;

    ref[1] = 2 * fact[2 * n] % MOD;
    ref[1] = (ref[1] - fact[n] + MOD) % MOD;

    ref[1] = (ref[1] - ref[0] + MOD) % MOD;

    ref[2] = 2 * fact[2 * n] % MOD;
    ref[2] = (ref[2] * choose(2 * n, n, MOD)) % MOD;
    ref[2] = (ref[2] * fact[n]) % MOD;
    FOR (i, n + 1) {
        ll tmp = choose(n, i, MOD) * choose(n, i, MOD) % MOD;
        tmp = (tmp * choose(2 * n - i, n, MOD)) % MOD;
        tmp = (tmp * fact[n]) % MOD;
        tmp = (tmp * fact[n]) % MOD;
        tmp = (tmp * fact[n]) % MOD;
        ref[2] = (ref[2] - tmp + MOD) % MOD;
    }

    ref[2] = (ref[2] - ref[1] + MOD) % MOD;
    ref[2] = (ref[2] - ref[0] + MOD) % MOD;

    ref[3] = fact[3 * n] % MOD;
    ref[3] = (ref[3] - ref[0] + MOD) % MOD;
    ref[3] = (ref[3] - ref[1] + MOD) % MOD;
    ref[3] = (ref[3] - ref[2] + MOD) % MOD;

    ll rv = (ref[1] + 2 * ref[2] + 3 * ref[3]) % MOD;
    cout << rv << '\n';
    return 0;
}