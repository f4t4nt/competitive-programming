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

vector<ll> factors(ll n) {
    vector<ll> rv;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            rv.pb(i);
            if (i * i != n) {
                rv.pb(n / i);
            }
        }
    }
    return rv;
}

bool valid(ll f, ll n) {
    // a - b + 1 = f, a + b + 2 = n / f
    // a - b = f - 1, a + b = n / f - 2
    ll a = (n / f - 2 + f - 1) / 2;
    ll b = (n / f - 2 - f + 1) / 2;
    return a - b == f - 1 && a + b == n / f - 2 && a > 0 && b > 0;
}

int main() {
    while (true) {
        str n_str;
        cin >> n_str;
        ll n = stoll(n_str);
        if (n == 0) {
            break;
        }
        n *= 2;
        vector<ll> fs = factors(n);
        ll rv = 0;
        FORE (f, fs) {
            if (valid(f, n)) {
                rv++;
            }
        }
        cout << rv << '\n';
    }
    return 0;
}