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

constexpr ll MOD = 1e9 + 7;

int main() {
    ll n, m;
    cin >> n >> m;
    vector<tuple<ll, ll, ll>> edges;
    FOR (i, m) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        edges.pb(mt(c, a, b));
    }
    vector<vector<pair<ll, ll>>> adj(n);
    ssort(edges);
    FORE (e, edges) {
        ll c, a, b;
        tie(c, a, b) = e;
        adj[a].pb(mp(b, c));
    }
    vector<tuple<ll, ll, ll, ll>> dist(n, mt(1e18, 1e18, 1e18, 1e18));
    dist[0] = mt(0, 1, 0, 0);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    pq.push(mp(0, 0));
    while (!pq.empty()) {
        ll d, v;
        tie(d, v) = pq.top();
        pq.pop();
        if (d > get<0>(dist[v])) {
            continue;
        }
        FORE (e, adj[v]) {
            ll u, c;
            tie(u, c) = e;
            if (get<0>(dist[u]) > d + c) {
                get<0>(dist[u]) = d + c;
                get<1>(dist[u]) = get<1>(dist[v]);
                get<2>(dist[u]) = get<2>(dist[v]) + 1;
                get<3>(dist[u]) = get<3>(dist[v]) + 1;
                pq.push(mp(d + c, u));
            } elif (get<0>(dist[u]) == d + c) {
                get<1>(dist[u]) = (get<1>(dist[u]) + get<1>(dist[v])) % MOD;
                get<2>(dist[u]) = min(get<2>(dist[u]), get<2>(dist[v]) + 1);
                get<3>(dist[u]) = max(get<3>(dist[u]), get<3>(dist[v]) + 1);
            }
        }
    }
    cout << get<0>(dist[n - 1]) << " " << get<1>(dist[n - 1]) << " " << get<2>(dist[n - 1]) << " " << get<3>(dist[n - 1]) << endl;
    return 0;
}