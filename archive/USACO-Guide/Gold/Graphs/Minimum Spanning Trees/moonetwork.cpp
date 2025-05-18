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
    ll n;
    cin >> n;
    vector<pair<ll, ll>> coords(n);
    vector<tuple<ll, ll, ll>> edges;
    DSU dsu(n);
    FOR (i, n) {
        cin >> coords[i].first >> coords[i].second;
    }
    ssort(coords);
    ll i = 0, j = 0, k = 0;
    while (k < 5 && j < n) {
        ll x2 = coords[j].first;
        while (j < n && coords[j].first == x2) {
            FOB (l, i, j) {
                ll x1 = coords[l].first;
                ll y1 = coords[l].second;
                ll y2 = coords[j].second;
                ll dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
                edges.pb(mt(dist, l, j));
            }
            j++;
        }
        k++;
    }
    while (j < n) {
        ll x2 = coords[j].first;
        while (j < n && coords[j].first == x2) {
            FOB (l, i, j) {
                ll x1 = coords[l].first;
                ll y1 = coords[l].second;
                ll y2 = coords[j].second;
                ll dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
                edges.pb(mt(dist, l, j));
            }
            j++;
        }
        ll x1 = coords[i].first;
        while (i < n && coords[i].first == x1) {
            i++;
        }
    }
    ssort(edges);
    ll rv = 0;
    FORE (edge, edges) {
        ll dist = get<0>(edge);
        ll a = get<1>(edge);
        ll b = get<2>(edge);
        if (dsu.unite(a, b)) {
            rv += dist;
        }
    }
    cout << rv << '\n';
    return 0;
}