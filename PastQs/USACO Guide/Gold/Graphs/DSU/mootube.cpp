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

// http://www.usaco.org/index.php?page=viewproblem2&cpid=789

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

struct Edge {
    ll r, p, q;
};

struct Query {
    ll k, v, i;
};

int main() {
    ifstream cin("mootube.in");
    ofstream cout("mootube.out");

    ll n, q;
    cin >> n >> q;
    vector<Edge> edges(n - 1);   
    FOR(i, n - 1) {
        ll p, q, r;
        cin >> p >> q >> r;
        edges[i] = { r, p - 1, q - 1 };
    }
    sort(edges.begin(), edges.end(), 
        [](const Edge &a, const Edge &b) { return a.r > b.r; });
    vector<Query> queries(q);
    FOR(i, q) {
        ll k, v;
        cin >> k >> v;
        queries[i] = { k, v - 1, i };
    }
    sort(queries.begin(), queries.end(), 
        [](const Query &a, const Query &b) { return a.k > b.k; });
    DSU dsu(n);
    vector<ll> rv(q);
    ll prev_k = 1e18, edge_i = 0;
    FOR(i, q) {
        if (queries[i].k != prev_k) {
            while (edge_i < n - 1 && edges[edge_i].r >= queries[i].k) {
                dsu.unite(edges[edge_i].p, edges[edge_i].q);
                edge_i++;
            }
            prev_k = queries[i].k;
        }
        rv[queries[i].i] = dsu.size(queries[i].v) - 1;
    }
    FOR(i, q) {
        cout << rv[i] << '\n';
    }
    return 0;
}