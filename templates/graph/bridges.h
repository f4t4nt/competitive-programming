#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

#define pb push_back
#define sz(C) (ll) C.size()

// -------------------------------------------------------------------------------
//  Bridge-finding (Tarjan, DFS low-link)
// -------------------------------------------------------------------------------
//  Finds all edges that are bridges (removing the edge increases # of components)
//  Works for undirected, connected or disconnected graphs; parallel edges handled
//  Complexity: O(n + m) time,  O(n) memory.
// -------------------------------------------------------------------------------
struct Bridges {
    ll n;                       // |V|
    vector<vector<ll>> &adj;    // external adjacency
    vector<ll> tin, low;        // discovery time & low-link
    vector<bool> vis;           // DFS visited
    ll timer = 0;               // global DFS timer
    set<pll> bridges;           // output list

    explicit Bridges(ll _n, vector<vector<ll>> &_adj)
        : n(_n), adj(_adj),
          tin(n, -1), low(n, -1), vis(n, false) {}

    set<pll> solve() {
        for (ll v = 0; v < n; v++)
            if (!vis[v]) dfs(v, -1);
        return bridges;
    }

private:
    void add_bridge(ll u, ll v) {
        if (u > v) swap(u, v);
        bridges.insert({u, v});
    }

    void dfs(ll v, ll p) {
        vis[v] = true;
        tin[v] = low[v] = timer++;

        bool parent_skipped = false;            // skip only one copy of the parent edge
        for (ll to : adj[v]) {
            if (to == p && !parent_skipped) {   // ignore the edge we came from
                parent_skipped = true;
                continue;
            }

            if (vis[to]) {                      // back-edge
                low[v] = min(low[v], tin[to]);
            } else {                            // tree-edge
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] > tin[v])           // no back-edge from subtree
                    add_bridge(v, to);
            }
        }
    }
};
