#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// -----------------------------------------------------------------------------
//  Strongly Connected Components (Tarjan)
// -----------------------------------------------------------------------------
//  Supports:   - ids[u]     component id of vertex u
//              - scc_cnt    number of components
//              - adj_scc    condensation graph, duplicate edges collapsed
//  Notes:      - ids come out in reverse topological order: every condensation
//                edge goes from a higher id to a lower id, so id 0 is a sink
//                and id scc_cnt - 1 is a source
//              - recursive dfs, depth can reach n
//  Complexity: O(n + m) build, plus m log m for adj_scc
// -----------------------------------------------------------------------------
struct SCCs {
    ll n, idx, scc_cnt;      // idx = next dfs timestamp
    vector<vector<ll>> adj;
    vector<set<ll>> adj_scc; // condensation: edges go high id -> low id
    vector<ll> ord, low;     // dfs entry time / lowest entry time reachable
    vector<ll> ids;          // ids[u] = component of u
    vector<bool> on_stack;
    stack<ll> stk;

    SCCs(ll n0, vector<vector<ll>> &adj0) {
        n = n0, idx = 0, scc_cnt = 0;
        adj = adj0;
        ord.assign(n, -1), low.assign(n, -1), ids.assign(n, -1);
        on_stack.assign(n, false);
        for (ll u = 0; u < n; u++) if (ord[u] == -1) dfs(u);
        adj_scc.assign(scc_cnt, {});
        for (ll u = 0; u < n; u++)
            for (ll v : adj[u])
                if (ids[u] != ids[v]) adj_scc[ids[u]].insert(ids[v]);
    }

    // pop one component when u closes its cycle (low == ord)
    void dfs(ll u) {
        ord[u] = low[u] = idx++;
        stk.push(u);
        on_stack[u] = true;
        for (ll v : adj[u]) {
            if (ord[v] == -1) dfs(v), low[u] = min(low[u], low[v]);
            else if (on_stack[v]) low[u] = min(low[u], ord[v]);
        }
        if (low[u] == ord[u]) {
            while (true) {
                ll v = stk.top();
                stk.pop();
                ids[v] = scc_cnt;
                on_stack[v] = false;
                if (u == v) break;
            }
            scc_cnt++;
        }
    }
};
