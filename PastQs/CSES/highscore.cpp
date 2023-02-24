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

int main() {
    ll n, m;
    cin >> n >> m;
    vector<tuple<ll, ll, ll>> edges(m);
    FOR (i, m) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        edges[i] = mt(a, b, c);
    }
    vector<vector<pair<ll, ll>>> adj(n);
    FORE (e, edges) {
        ll a, b, c;
        tie(a, b, c) = e;
        adj[a].pb(mp(b, c));
    }
    vector<ll> dist(n, -1e18), prev(n, -1);
    vector<bool> cycle(n);
    dist[0] = 0;
    FOR (i, 2 * n) {
        FORE (e, edges) {
            ll a, b, c;
            tie(a, b, c) = e;
            if (i < n) {
                if (dist[a] != -1e18 && dist[a] + c > dist[b]) {
                    dist[b] = dist[a] + c;
                    prev[b] = a;
                }
            } else {
                if (dist[a] != -1e18 && dist[a] + c > dist[b]) {
                    dist[b] = dist[a] + c;
                    prev[b] = a;
                    cycle[b] = true;
                }
                if (cycle[a]) {
                    cycle[b] = true;
                }
            }
        }
    }
    vector<bool> visited(n, false);
    ll cur = n - 1;
    while (cur != -1 && !visited[cur]) {
        visited[cur] = true;
        cur = prev[cur];
    }
    if (cur == -1 && dist[n - 1] != -1e18 && !cycle[n - 1]) {
        cout << dist[n - 1] << '\n';
    } else {
        cout << -1 << '\n';
    }
    return 0;
}