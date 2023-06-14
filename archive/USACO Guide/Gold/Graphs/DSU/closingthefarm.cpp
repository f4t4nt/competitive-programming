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

// http://www.usaco.org/index.php?page=viewproblem2&cpid=646

struct DSU {
	vector<ll> e;
	DSU(ll N) { e = vector<ll>(N, -1); }
	ll get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool same_set(ll a, ll b) { return get(a) == get(b); }
	ll size(ll x) { return -e[get(x)]; }
	bool unite(ll x, ll y) {
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
		return true;
	}
};

int main() {
    ifstream cin("closing.in");
    ofstream cout("closing.out");

    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> e(n);
    FOR(i, m) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        e[a].pb(b);
        e[b].pb(a);
    }
    vector<ll> o(n);
    FOR(i, n) {
        cin >> o[i];
        o[i]--;
    }
    DSU dsu(n);
    vector<bool> v(n), rv(n);
    FORR(i, n) {
        ll &x = o[i];
        v[x] = true;
        FORE(y, e[x]) {
            if (v[y]) {
                dsu.unite(x, y);
            }
        }
        rv[i] = dsu.size(x) == (n - i);
    }
    FOR(i, n) {
        if (rv[i]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}