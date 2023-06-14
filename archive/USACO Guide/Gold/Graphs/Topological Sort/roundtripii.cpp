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

vector<ll> cycle(ll &n, vector<vector<ll>> &adj) {
    vector<bool> vis(n);
    vector<ll> par(n, -1), cyc;
    function<bool(ll)> dfs = [&](ll v) {
        vis[v] = true;
        FORE(u, adj[v]) {
            if (!vis[u]) {
                par[u] = v;
                if (dfs(u)) {
                    return true;
                }
            } elif (vis[u]) {
                cyc.pb(u);
                while (v != u) {
                    cyc.pb(v);
                    v = par[v];
                }
                cyc.pb(u);
                return true;
            }
        }
        vis[v] = false;
        return false;
    };
    FOR(i, n) {
        if (dfs(i)) {
            return cyc;
        }
    }
    return {};
}

int main() {
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n);
    FOR(i, m) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
    }
    vector<ll> in(n);
    FORE(v, adj) {
        FORE(u, v) {
            in[u]++;
        }
    }
    queue<ll> q;
    FOR(i, n) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    vector<ll> top_sort;
    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        top_sort.pb(v);
        FORE(u, adj[v]) {
            in[u]--;
            if (in[u] == 0) {
                q.push(u);
            }
        }
    }
    if (sz(top_sort) == n) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    vector<ll> cyc = cycle(n, adj);
    if (cyc.empty()) {
        cout << "IMPOSSIBLE\n";
    } else {
        flip(cyc);
        cout << sz(cyc) << '\n';
        FORE(x, cyc) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }
    return 0;
}