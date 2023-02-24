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

constexpr ll MOD = 998244353;

vector<ll> pow(ll n, ll m) {
    vector<ll> rv;
    m %= MOD;
    rv.pb(m);
    FOR(i, n - 1) {
        rv.pb((rv.back() * m) % MOD);
    }
    return rv;
}

ll sum_vec(vector<ll> v) {
    ll rv = 0;
    FORE(x, v) {
        rv += x;
        rv %= MOD;
    }
    return rv;
}

bool is_prime(ll x) {
    if (x == 1) {
        return false;
    }
    ll p = 2;
    while (p*p <= x) {
        if (x % p == 0) {
            return false;
        }
        p++;
    }
    return true;
}

vector<ll> goobermagic(ll n, ll m) {
    vector<ll> rv(n);
    ll prev = 1, prod = 1;
    FOR(i, n) {
        if (is_prime(i + 1)) {
            prod *= (i + 1);
        }
        rv[i] = (prev * ((m / prod) % MOD)) % MOD;
        prev = rv[i];
    }
    return rv;
}

int main() {
    ll n, m;
    cin >> n >> m;
    vector<ll> rv = pow(n, m), comps = goobermagic(n, m);
    FOR(i, n) {
        rv[i] = (rv[i] - comps[i] + MOD) % MOD;
    }
    cout << sum_vec(rv) << '\n';
    return 0;
}