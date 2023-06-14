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

vector<pair<ll, ll>> decompose(ll &n, ll &m, vector<ll> &a) {
    vector<pair<ll, ll>> rv;
    FOR(i, n) {
        ll x = a[i], y = 1;
        while(x % m == 0) {
            x /= m;
            y *= m;
        }
        if(sz(rv) && rv[sz(rv) - 1].first == x) {
            rv[sz(rv) - 1].second += y;
        } else {
            rv.pb(mp(x, y));
        }
    }
    return rv;
}

bool valid(ll &n, ll &m, ll &k, vector<ll> &a, vector<ll> &b) {
    vector<pair<ll, ll>> tmpa = decompose(n, m, a), tmpb = decompose(k, m, b);
    if(sz(tmpa) != sz(tmpb)) {
        return false;
    }
    FOR(i, sz(tmpa)) {
        if(tmpa[i] != tmpb[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ll t;
    cin >> t;
    while(t--) {
        ll n, m, k, sa = 0, sb = 0;
        cin >> n >> m;
        vector<ll> a(n);
        FOR(i, n) {
            cin >> a[i];
            sa += a[i];
        }
        cin >> k;
        vector<ll> b(k);
        FOR(i, k) {
            cin >> b[i];
            sb += b[i];
        }
        if(sa == sb && valid(n, m, k, a, b)) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}