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

// https://cses.fi/problemset/task/2413/

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
    friend ostream &operator<<(ostream &os, const mod_ll &m) { return os << m.val; }
};

int main() {
    ll t;
    cin >> t;
    vector<pair<mod_ll, mod_ll>> dp(1e6 + 1);
    dp[1] = {1, 1};
    FOB(i, 2, 1e6 + 1) {
        dp[i].first = dp[i - 1].second + dp[i - 1].first * 4;
        dp[i].second = dp[i - 1].second * 2 + dp[i - 1].first;
    }
    while (t--) {
        ll n;
        cin >> n;
        cout << dp[n].first + dp[n].second << '\n';
    }
    return 0;
}