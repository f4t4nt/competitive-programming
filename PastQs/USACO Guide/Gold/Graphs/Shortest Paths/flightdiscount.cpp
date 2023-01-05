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
    vector<tuple<ll, ll, ll>> edges;
    FOR (i, m) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        edges.pb(mt(a, b, c));
    }
    vector<vector<pair<ll, ll>>> adj(n);
    FORE (edge, edges) {
        auto [a, b, c] = edge;
        adj[a].pb(mp(b, c));
    }
    vector<pair<ll, ll>> dist(n, mp(1e18, 1e18));
    dist[0].first = 0;
    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<>> pq;
    pq.push(mt(0, 0, 0));
    while (!pq.empty()) {
        auto [d, node, coupon] = pq.top();
        pq.pop();
        if (coupon == 0 && dist[node].first < d) {
            continue;
        } elif (coupon == 1 && dist[node].second < d) {
            continue;
        }
        FORE (edge, adj[node]) {
            auto [to, cost] = edge;
            if (coupon == 0 && dist[to].first > d + cost) {
                dist[to].first = d + cost;
                pq.push(mt(dist[to].first, to, 0));
            }
            if (coupon == 0 && dist[to].second > d + cost / 2) {
                dist[to].second = d + cost / 2;
                pq.push(mt(dist[to].second, to, 1));
            }
            if (coupon == 1 && dist[to].second > d + cost) {
                dist[to].second = d + cost;
                pq.push(mt(dist[to].second, to, 1));
            }
        }
    }
    cout << dist[n - 1].second << '\n';
    return 0;
}