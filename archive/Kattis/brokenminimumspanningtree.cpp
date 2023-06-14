#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
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

void dfs(ll u, vector<bool> &vis, vector<vector<pair<ll, ll>>> &adj) {
    vis[u] = true;
    FORE (e, adj[u]) {
        ll v = e.first;
        if (!vis[v]) dfs(v, vis, adj);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    // v, w
    vector<vector<pair<ll, ll>>> adj0(n);
    // w, u, v, i
    vector<tuple<ll, ll, ll, ll>> eth_edges, edges;
    FOR (i, m) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges.pb({w,u,v,i});
        if (i < n - 1) {
            eth_edges.pb({w,u,v,i});
            adj0[u].pb({v,w});
            adj0[v].pb({u,w});
        }
    }
    rsort(eth_edges);
    ssort(edges);

    vector<pair<ll, ll>> rv;
    FOR (idx, n - 1) {
        ll w, u, v, i;
        tie(w,u,v,i) = eth_edges[idx];
        auto adj = adj0;
        FOR (j, sz(adj[u])) {
            if (adj[u][j].first == v && adj[u][j].second == w) {
                adj[u].erase(adj[u].begin() + j);
            }
        }
        FOR (j, sz(adj[v])) {
            if (adj[v][j].first == u && adj[v][j].second == w) {
                adj[v].erase(adj[v].begin() + j);
            }
        }
        vector<bool> vis(n);
        dfs(0, vis, adj);
        FOR (j, sz(edges)) {
            ll nw, nu, nv, ni;
            tie(nw,nu,nv,ni) = edges[j];
            if (vis[nu] == vis[nv]) continue;
            if (nw < w) {
                rv.pb({i,ni});
                adj0 = adj;
                adj0[nu].pb({nv,nw});
                adj0[nv].pb({nu,nw});
            }
            break;
        }
    }

    cout << sz(rv) << '\n';
    FORE (e, rv) {
        cout << e.first + 1 << ' ' << e.second + 1 << '\n';
    }

    return 0;
}