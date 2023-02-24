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
    }
    vector<vector<ll>> adj(n);
    FORE (e, edges) {
        adj[e.first].pb(e.second);
        adj[e.second].pb(e.first);
    }
    ll rv = 1e18;
    FOR (i, n) {
        vector<ll> dist(n, 1e18);
        dist[i] = 0;
        queue<pair<ll, ll>> q;
        q.push({i, -1});
        while (!q.empty()) {
            ll u = q.front().first;
            ll p = q.front().second;
            q.pop();
            FORE (v, adj[u]) {
                if (v == p) {
                    continue;
                }
                if (dist[v] == 1e18) {
                    dist[v] = dist[u] + 1;
                    q.push({v, u});
                } else {
                    rv = min(rv, dist[u] + dist[v] + 1);
                }
            }
        }
    }
    if (rv == 1e18) {
        cout << "impossible\n";
    } else {
        cout << rv << '\n';
    }
    return 0;
}