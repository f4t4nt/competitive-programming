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
map<ll, ll> inv_map;

struct mod_ll {
    ll val;
    mod_ll(ll v = 0) : val(((v % MOD) + MOD) % MOD) {}
    mod_ll operator+(const mod_ll &other) const { return mod_ll(val + other.val); }
    mod_ll operator-(const mod_ll &other) const { return mod_ll(val - other.val); }
    mod_ll operator*(const mod_ll &other) const { return mod_ll(val * other.val); }
    mod_ll pow(ll p) const {
        mod_ll rv = 1;
        mod_ll base = *this;
        while (p) {
            if (p & 1) rv = rv * base;
            base = base * base;
            p >>= 1;
        }
        return rv;
    }
    mod_ll inv() const {
        if (inv_map.find(val) != inv_map.end()) return mod_ll(inv_map[val]);
        return inv_map[val] = pow(MOD - 2).val;
    }
    mod_ll operator/(const mod_ll &other) const { return *this * other.inv(); }
};

struct Complex {
    mod_ll re, im;
    Complex(mod_ll r = 0, mod_ll i = 0) : re(r), im(i) {}
    Complex operator+(const Complex &other) const { return Complex(re + other.re, im + other.im); }
    Complex operator-(const Complex &other) const { return Complex(re - other.re, im - other.im); }
    Complex operator*(const Complex &other) const { return Complex(re * other.re - im * other.im, re * other.im + im * other.re); }
    Complex operator/(const Complex &other) const { return Complex((re * other.re + im * other.im) / (other.re * other.re + other.im * other.im), (im * other.re - re * other.im) / (other.re * other.re + other.im * other.im)); }
};

int main() {
    ll n;
    mod_ll a, b;
    cin >> a.val >> b.val >> n;
    Complex rv = Complex(-1, 0),
            base = Complex((a * a - b * b) / (a * a + b * b), ((mod_ll) (-2) * a * b) / (a * a + b * b));
    n++;
    while (n) {
        if (n & 1) {
            rv = rv * base;
        }
        base = base * base;
        n >>= 1;
    }
    cout << rv.re.val << '\n';
    return 0;
}