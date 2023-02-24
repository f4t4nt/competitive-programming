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

map<ch, ll> colors = {
    {'R', 0},
    {'O', 1},
    {'Y', 2},
    {'G', 3},
    {'B', 4},
    {'I', 5},
    {'V', 6}
};

int main() {
    ll n, m;
    cin >> n >> m;
    vector<tuple<ll, ll, ll, ll>> edges(m);
    FOR (i, m) {
        ll l1, l2, d;
        ch c;
        cin >> l1 >> l2 >> d >> c;
        l1--, l2--;
        edges[i] = mt(l1, l2, d, colors[c]);
    }
    vector<vector<ll>> dist(n, vector<ll>(1 << 7, 1e18));
    dist[0][0] = 0;
    FOR (i, n) {
        FORE (edge, edges) {
            ll l1, l2, d, c;
            tie(l1, l2, d, c) = edge;
            FOR (mask, 1 << 7) {
                ll next = mask | (1 << c);
                if (dist[l1][mask] != 1e18) {
                    dist[l2][next] = min(dist[l2][next], dist[l1][mask] + d);
                }
                if (dist[l2][mask] != 1e18) {
                    dist[l1][next] = min(dist[l1][next], dist[l2][mask] + d);
                }
            }
        }
    }
    cout << dist[0][(1 << 7) - 1] << '\n';
    return 0;
}