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

// https://codeforces.com/contest/1627/problem/E

struct Ladder {
    // ladder from (a, b) to (c, d) with +hp h
    ll a, b, c, d, h;
};

int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll n, m, k;
        cin >> n >> m >> k;
        vector<ll> x(n);
        FOR (i, n) {
            cin >> x[i];
        }
        vector<Ladder> ladders(k);
        map<pair<ll, ll>, ll> coords;
        coords[mp(0, 0)] = sz(coords);
        coords[mp(n - 1, m - 1)] = sz(coords);
        FOR (i, k) {
            cin >> ladders[i].a >> ladders[i].b >> ladders[i].c >> ladders[i].d >> ladders[i].h;
            ladders[i].a--, ladders[i].b--, ladders[i].c--, ladders[i].d--;
            if (coords.count(mp(ladders[i].a, ladders[i].b)) == 0) {
                coords[mp(ladders[i].a, ladders[i].b)] = sz(coords);
            }
            if (coords.count(mp(ladders[i].c, ladders[i].d)) == 0) {
                coords[mp(ladders[i].c, ladders[i].d)] = sz(coords);
            }
        }
        vector<tuple<ll, ll, ll>> edges;
        FORE (l, ladders) {
            edges.pb(mt(coords[mp(l.a, l.b)], coords[mp(l.c, l.d)], -l.h));
        }
        FORE (c1, coords) {
            FORE (c2, coords) {
                if (c1.first.first == c2.first.first && c1.first.second != c2.first.second) {
                    edges.pb(mt(c1.second, c2.second, abs(c1.first.second - c2.first.second) * x[c1.first.first]));
                }
            }
        }
        vector<vector<pair<ll, ll>>> adj(sz(coords));
        FORE (e, edges) {
            adj[get<0>(e)].pb(mp(get<1>(e), get<2>(e)));
        }
        vector<ll> dist(sz(coords), 1e18);
        dist[coords[mp(0, 0)]] = 0;
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
        pq.push(mp(0, coords[mp(0, 0)]));
        while (!pq.empty()) {
            ll d = pq.top().first;
            ll v = pq.top().second;
            pq.pop();
            if (d > dist[v]) {
                continue;
            }
            FORE (e, adj[v]) {
                if (dist[e.first] > dist[v] + e.second) {
                    dist[e.first] = dist[v] + e.second;
                    pq.push(mp(dist[e.first], e.first));
                }
            }
        }
        if (dist[coords[mp(n - 1, m - 1)]] == 1e18) {
            cout << "NO ESCAPE\n";
        } else {
            cout << dist[coords[mp(n - 1, m - 1)]] << '\n';
        }
    }
    return 0;
}