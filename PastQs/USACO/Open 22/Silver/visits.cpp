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

// http://usaco.org/index.php?page=viewproblem2&cpid=1230

struct DSU {
    vector<ll> e;
    void init(ll n) {
        FOR(i, n) e.pb(i);
    }
    ll find(ll x) {
        if (e[x] == x) return x;
        return e[x] = find(e[x]);
    }
    bool merge(ll x, ll y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        e[x] = y;
        return true;
    }
};

int main() {
    ll n;
    cin >> n;
    vector<tuple<ll, ll, ll>> e;
    FOR(i, n) {
        ll a, v;
        cin >> a >> v;
        e.pb({ v, i, a - 1 });
    }
    rsort(e);
    DSU d;
    d.init(n);
    ll rv = 0;
    FORE(t, e) {
        ll v, i, a;
        tie(v, i, a) = t;
        if (d.merge(i, a)) {
            rv += v;
        }
    }
    cout << rv << '\n';
    return 0;
}