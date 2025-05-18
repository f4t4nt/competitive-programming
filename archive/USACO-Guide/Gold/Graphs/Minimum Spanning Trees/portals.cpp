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

struct Portal {
    ll ends[2] = {-1, -1};
    void add(ll a) {
        if (ends[0] == -1) {
            ends[0] = a;
        } else {
            ends[1] = a;
        }
    }
    ll get(ll a) {
        if (ends[0] == a) {
            return ends[1];
        } else {
            return ends[0];
        }
    }
};

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
    ll n, rv = 0;
    cin >> n;
    vector<pair<ll, ll>> costs(n);
    vector<Portal> portals(2 * n);
    DSU dsu(2 * n);
    FOR (i, n) {
        cin >> costs[i].first;
        costs[i].second = i;
        vector<ll> p(4);
        FOR (j, 4) {
            cin >> p[j];
            p[j]--;
        }
        portals[p[0]].add(2 * i);
        portals[p[1]].add(2 * i);
        portals[p[2]].add(2 * i + 1);
        portals[p[3]].add(2 * i + 1);
    }
    ssort(costs);
    FORE (p, portals) {
        dsu.unite(p.ends[0], p.ends[1]);
    }
    ll i = 0;
    while (dsu.size(0) != 2 * n && i < n) {
        if (dsu.unite(costs[i].second * 2, costs[i].second * 2 + 1)) {
            rv += costs[i].first;
        }
        i++;
    }
    cout << rv << '\n';
    return 0;
}