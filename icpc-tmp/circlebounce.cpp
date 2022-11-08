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

struct Complex {
    ll re, im;
    Complex(ll re = 0, ll im = 0) : re((re % MOD + MOD) % MOD), im((im % MOD + MOD) % MOD) {}
    Complex operator*(const Complex &other) const {
        ll tmp = -im * other.im;
        tmp = (tmp % MOD + MOD) % MOD;
        return Complex((re * other.re % MOD + tmp) % MOD, (re * other.im % MOD + im * other.re % MOD) % MOD);
    }
};

ll pow(ll a, ll b) {
    ll rv = 1;
    while (b) {
        if (b & 1) {
            rv = rv * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return rv;
}

ll inv(ll a, map<ll, ll> &inv_ref) {
    if (inv_ref.find(a) != inv_ref.end()) {
        return inv_ref[a];
    }
    return inv_ref[a] = pow(a, MOD - 2);
}

int main() {
    ll a, b, n;
    cin >> a >> b >> n;
    map<ll, ll> inv_ref;
    Complex rv = Complex(-1, 0),
        mul = Complex((a * a + ((-b * b) % MOD + MOD) % MOD) % MOD * inv(a * a % MOD + b * b % MOD, inv_ref) % MOD,
                        (((MOD - 2) * a) % MOD * b) % MOD * inv(a * a % MOD + b * b % MOD, inv_ref) % MOD);
    n++;
    while (n) {
        if (n & 1) {
            rv = rv * mul;
        }
        mul = mul * mul;
        n >>= 1;
    }
    cout << rv.re << '\n';
    return 0;
}