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
    ll n;
    cin >> n;
    ll x_s, y_s, x_t, y_t;
    cin >> x_s >> y_s >> x_t >> y_t;
    map<pair<ll, ll>, ll> m;
    map<ll, vector<ll>> xs, ys;
    vector<vector<ll>> adj(n);
    FOR(i, n) {
        ll x, y;
        cin >> x >> y;
        m[mp(x, y)] = i;
        ys[x].pb(y);
        xs[y].pb(x);
    }
    FORE (x, xs) {
        ssort(x.second);
    }
    FORE (y, ys) {
        ssort(y.second);
    }
    ll s = m[mp(x_s, y_s)], t = m[mp(x_t, y_t)], idx = 0;
    FORE (elem, m) {
        ll x = elem.first.first, y = elem.first.second, i = elem.second;
        vector<ll> &adj_ys = ys[x];
        ll idx_y = lower_bound(adj_ys.begin(), adj_ys.end(), y) - adj_ys.begin();
        idx_y += 2;
        if (idx_y < sz(adj_ys)) {
            ll y_ = adj_ys[idx_y];
            vector<ll> &adj_xs = xs[y_];
            ll idx_x = lower_bound(adj_xs.begin(), adj_xs.end(), x) - adj_xs.begin();
            idx_x++;
            if (idx_x < sz(adj_xs)) {
                ll x_ = adj_xs[idx_x];
                adj[i].pb(m[mp(x_, y_)]);
            }
            idx_x -= 2;
            if (idx_x >= 0) {
                ll x_ = adj_xs[idx_x];
                adj[i].pb(m[mp(x_, y_)]);
            }
        }
        idx_y -= 4;
        if (idx_y >= 0) {
            ll y_ = adj_ys[idx_y];
            vector<ll> &adj_xs = xs[y_];
            ll idx_x = lower_bound(adj_xs.begin(), adj_xs.end(), x) - adj_xs.begin();
            idx_x++;
            if (idx_x < sz(adj_xs)) {
                ll x_ = adj_xs[idx_x];
                adj[i].pb(m[mp(x_, y_)]);
            }
            idx_x -= 2;
            if (idx_x >= 0) {
                ll x_ = adj_xs[idx_x];
                adj[i].pb(m[mp(x_, y_)]);
            }
        }
        vector<ll> &adj_xs = xs[y];
        ll idx_x = lower_bound(adj_xs.begin(), adj_xs.end(), x) - adj_xs.begin();
        idx_x += 2;
        if (idx_x < sz(adj_xs)) {
            ll x_ = adj_xs[idx_x];
            vector<ll> &adj_ys = ys[x_];
            ll idx_y = lower_bound(adj_ys.begin(), adj_ys.end(), y) - adj_ys.begin();
            idx_y++;
            if (idx_y < sz(adj_ys)) {
                ll y_ = adj_ys[idx_y];
                adj[i].pb(m[mp(x_, y_)]);
            }
            idx_y -= 2;
            if (idx_y >= 0) {
                ll y_ = adj_ys[idx_y];
                adj[i].pb(m[mp(x_, y_)]);
            }
        }
        idx_x -= 4;
        if (idx_x >= 0) {
            ll x_ = adj_xs[idx_x];
            vector<ll> &adj_ys = ys[x_];
            ll idx_y = lower_bound(adj_ys.begin(), adj_ys.end(), y) - adj_ys.begin();
            idx_y++;
            if (idx_y < sz(adj_ys)) {
                ll y_ = adj_ys[idx_y];
                adj[i].pb(m[mp(x_, y_)]);
            }
            idx_y -= 2;
            if (idx_y >= 0) {
                ll y_ = adj_ys[idx_y];
                adj[i].pb(m[mp(x_, y_)]);
            }
        }
    }
    vector<ll> dist(n, 1e18);
    dist[s] = 0;
    queue<ll> bfs;
    bfs.push(s);
    while (!bfs.empty() && dist[t] == 1e18) {
        ll u = bfs.front();
        bfs.pop();
        FORE (v, adj[u]) {
            if (dist[v] == 1e18) {
                dist[v] = dist[u] + 1;
                bfs.push(v);
            }
        }
    }
    if (dist[t] == 1e18) {
        cout << -1 << '\n';
    } else {
        cout << dist[t] << '\n';
    }
    return 0;
}