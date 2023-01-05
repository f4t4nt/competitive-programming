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

struct pipe {
    ll a, b, c, f;
};

int main() {
    // ifstream cin("pump.in");
    // ofstream cout("pump.out");

    ll n, m;
    cin >> n >> m;
    vector<pipe> pipes(m);
    FOR (i, m) {
        cin >> pipes[i].a >> pipes[i].b >> pipes[i].c >> pipes[i].f;
        pipes[i].a--;
        pipes[i].b--;
    }
    vector<vector<pipe>> adj(n);
    FORE (p, pipes) {
        adj[p.a].pb(p);
        adj[p.b].pb(p);
    }
    vector<map<ll, ll>> dist(n);
    dist[0][1e18] = 0;
    priority_queue<pair<ll, pair<ll, ll>>, vector<pair<ll, pair<ll, ll>>>, greater<>> q;
    q.push({0, {0, 1e18}});
    while (!q.empty()) {
        auto [d, p] = q.top();
        q.pop();
        if (dist[p.first].count(p.second) && dist[p.first][p.second] < d) {
            continue;
        }
        FORE (e, adj[p.first]) {
            ll nd = d + e.c;
            ll nf = min(p.second, e.f);
            ll c = e.a ^ e.b ^ p.first;
            if (!dist[c].count(nf) || dist[c][nf] > nd) {
                dist[c][nf] = nd;
                q.push({nd, {c, nf}});
            }
        }
    }
    pair<ll, ll> best = {0, 1};
    FORE (p, dist[n - 1]) {
        if (p.first * best.second > p.second * best.first) {
            best = {p.first, p.second};
        }
    } 
    cout << best.first * 1000000 / best.second << '\n';
    return 0;
}