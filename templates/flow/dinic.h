#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<ll, ll> pll;

#define pb push_back
#define sz(C) (ll) C.size()

const ll INF = 1e18;

// directed edge in the residual graph
// - cap  = residual capacity on this edge (forward edge gets original cap)
// - cost = 0 here (kept for symmetry with MCMF template)
// - flow = current flow (can be < 0 on a reverse edge)
struct Edge {
    ll s, t, cap = 0, cost = 0, flow = 0;
};

struct Dinic {
    ll n;                       // |V|
    vector<Edge> edges;         // forward & reverse; reverse index = e ^ 1
    vector<vector<ll>> adj;     // adjacency list of edge indices
    vector<ll> lvl, ptr;        // BFS level graph & current-arc optimisation
    queue<ll> q;

    // constructor; expects only forward edges
    Dinic(ll _n, vector<Edge> &_e) :
        n(_n), adj(_n), lvl(_n), ptr(_n)
    {
        for (auto &e : _e) {
            adj[e.s].pb(sz(edges)); edges.pb(e);            // forward
            adj[e.t].pb(sz(edges)); edges.pb({ e.t, e.s }); // reverse
        }
    }

    // builds the level graph, returns false if t is unreachable from s
    bool bfs(ll s, ll t) {
        lvl.assign(n, -1); lvl[s] = 0; q.push(s);
        while (!q.empty()) {
            ll v = q.front(); q.pop();
            for (ll id : adj[v]) {
                ll u = edges[id].t;
                if (lvl[u] != -1 || edges[id].cap <= edges[id].flow) continue;
                lvl[u] = lvl[v] + 1;
                q.push(u);
            }
        }
        return lvl[t] != -1;
    }

    // sends blocking flow along the level graph, returns amount of flow actually pushed
    ll dfs(ll v, ll t, ll f) {
        if (!f || v == t) return f;
        for (ll &cid = ptr[v]; cid < sz(adj[v]); cid++) {
            ll id = adj[v][cid], u = edges[id].t;
            if (lvl[u] != lvl[v] + 1) continue;
            ll pushed = dfs(u, t, min(f, edges[id].cap-edges[id].flow));
            if (pushed) {
                edges[id].flow      += pushed;
                edges[id ^ 1].flow  -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    // computes the maximum s-t flow
    // O(E sqrt V) typical, O(E V) worst-case
    ll max_flow(ll s, ll t) {
        ll flow = 0;
        while (bfs(s, t)) {
            ptr.assign(n, 0);
            while (ll pushed = dfs(s, t, INF)) flow += pushed;
        }
        return flow;
    }

    // edges crossing (reachable -> unreachable) form a minimum s-t cut
    vector<pll> min_cut(ll s, ll t) {
        bfs(s, t);
        vector<pll> cut;
        for (auto &e : edges)
            if (lvl[e.s] != -1 && lvl[e.t] == -1 && e.cap > 0)
                cut.pb({ e.s, e.t });
        return cut;
    }

    // assumes path is a simple list of vertices currently present
    // in the residual graph; reduces flow by f along that path
    void undo_flow(vector<ll> path, ll f) {
        for (ll i = 0; i + 1 < sz(path); i++) {
            for (ll e : adj[path[i]]) if (edges[e].t == path[i + 1]) {
                edges[e].flow     -= f;
                edges[e ^ 1].flow += f;
                assert(edges[e].flow      <= edges[e].cap);
                assert(edges[e ^ 1].flow  <= edges[e ^ 1].cap);
                break;
            }
        }
    }

    // retrieves all paths from source to sink
    void get_paths(ll s, ll t, ll flow, vector<vector<ll>> &paths) {
        vector<ll> ptr(n);
        vector<vector<ll>> adjv(n);
        for (auto &e : edges)
            if (e.cap > 0 && e.flow > 0)
                adjv[e.s].pb(e.t);

        function<bool(ll, vector<ll>&)> dfs = [&](ll v, vector<ll> &path) {
            path.pb(v);
            if (v == t) return true;
            while (ptr[v] < sz(adjv[v])) {
                ll u = adjv[v][ptr[v]++];
                if (dfs(u, path)) return true;
            }
            path.pop_back();
            return false;
        };

        for (ll i = 0; i < flow; i++) {
            vector<ll> path;
            assert(dfs(s, path));
            paths.pb(path);
        }
    }
};
