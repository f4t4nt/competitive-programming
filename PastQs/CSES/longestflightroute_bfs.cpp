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
    vector<pair<ll, ll>> edges(m);
    FOR (i, m) {
        cin >> edges[i].first >> edges[i].second;
        edges[i].first--, edges[i].second--;
    }
    vector<vector<ll>> adj(n);
    FORE (e, edges) {
        adj[e.first].pb(e.second);
    }
    vector<ll> dist(n, -1), parent(n, -1), visited(n);
    priority_queue<pair<ll, ll>> q;
    q.push(mp(0, 0));
    dist[0] = 0;
    while (!q.empty()) {
        ll u = q.top().second, d = q.top().first;
        q.pop();
        if (d < dist[u]) {
            continue;
        }
        FORE (v, adj[u]) {
            if (dist[v] < dist[u] + 1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                if (visited[v] < 100) {
                    visited[v]++;
                    q.push(mp(dist[v], v));
                }
            }
        }
    }
    if (dist[n - 1] == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        vector<ll> path;
        ll u = n - 1;
        while (u != -1) {
            path.pb(u);
            u = parent[u];
        }
        flip(path);
        cout << sz(path) << '\n';
        FORE (p, path) {
            cout << p + 1 << ' ';
        }
        cout << '\n';
    }
    return 0;
}