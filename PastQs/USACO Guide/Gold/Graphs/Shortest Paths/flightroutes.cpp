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
    ll n, m, k;
    cin >> n >> m >> k;
    ll k2 = k + 1;
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
    vector<multiset<ll>> dists(n);
    dists[0].insert(0);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    pq.push(mp(0, 0));
    while (!pq.empty()) {
        ll d, u;
        tie(d, u) = pq.top();
        pq.pop();
        if (d > *dists[u].rbegin()) {
            continue;
        }
        FORE (v, adj[u]) {
            ll nd = d + v.second;
            if (sz(dists[v.first]) < k2) {
                dists[v.first].insert(nd);
                pq.push(mp(nd, v.first));
            } elif (nd < *dists[v.first].rbegin()) {
                dists[v.first].erase(*dists[v.first].rbegin());
                dists[v.first].insert(nd);
                pq.push(mp(nd, v.first));
            }
        }
    }
    ll i = 0;
    FORE (d, dists[n - 1]) {
        if (i == k) {
            break;
        }
        cout << d << ' ';
        i++;
    }
    cout << '\n';
    return 0;
}