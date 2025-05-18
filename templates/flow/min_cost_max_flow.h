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

struct MinCostMaxFlow {
    ll n;                       // |V|
    vector<Edge> edges;         // forward & reverse; reverse index = e ^ 1; reverse cost = -cost
    vector<vector<ll>> adj;     // adjacency list of edge indices

    vector<ll> dist, pi;        // D'Esopo-Johnson potentials
    vector<ll> vis;             // visited in Dijkstra
    vector<ll> par;             // predecessor edge on shortest path

    // constructor; expects only forward edges
    MinCostMaxFlow(ll _n, vector<Edge> &_e) :
        n(_n), adj(_n),
        dist(_n), pi(_n), vis(_n), par(_n)
    {
        for (auto &e : _e) {
            adj[e.s].pb(sz(edges)); edges.pb(e);                            // forward
            adj[e.t].pb(sz(edges)); edges.pb({ e.t, e.s, 0, -e.cost });     // reverse
        }
    }

    // Bellman-Ford to initialise Johnson potentials if negative costs exist
    void set_pi(ll s) {
        pi.assign(n, INF);
        pi[s] = 0;
        bool changed = true;
        for (ll it = 0; it < n && changed; it++) {
            changed = false;
            for (auto &e : edges)
                if (e.cap && pi[e.s] < INF && pi[e.s] + e.cost<pi[e.t]) {
                    pi[e.t] = pi[e.s] + e.cost; changed = true;
                }
        }
    }

    // Dijkstra; returns true if sink is reachable
    bool dijkstra(ll s, ll t) {
        vis.assign(n, 0);
        dist.assign(n, INF);
        dist[s] = 0;

        using PQ = __gnu_pbds::priority_queue<pll, greater<>>;
        PQ pq; vector<PQ::point_iterator> its(n, pq.end());
        its[s] = pq.push({0, s});

        while (!pq.empty()) {
            ll v = pq.top().second; pq.pop();
            if (vis[v]) continue;
            vis[v] = 1;
            for (ll id : adj[v]) {
                Edge &e = edges[id];
                ll cap = e.cap - e.flow;
                if (cap == 0) continue;
                ll u = e.t;
                ll rcost = e.cost + pi[v] - pi[u];
                if (dist[v] + rcost < dist[u]) {
                    dist[u] = dist[v] + rcost;
                    par[u] = id;
                    if (its[u] == pq.end()) its[u] = pq.push({ dist[u], u });
                    else                    pq.modify(its[u], { dist[u], u });
                }
            }
        }
        for (ll v = 0; v < n; v++) if (dist[v] < INF) pi[v] += dist[v];
        return vis[t];
    }

    // returns {max_flow , min_cost}
    // O(F m log n)
    pll max_flow(ll s, ll t) {
        ll flow = 0, cost = 0;
        while (dijkstra(s, t)) {
            ll f = INF;
            // bottleneck
            for (ll v = t; v != s; v = edges[par[v] ^ 1].t)
                f = min(f, edges[par[v]].cap - edges[par[v]].flow);

            // augment and accumulate cost on-the-fly
            for (ll v = t; v != s; v = edges[par[v] ^ 1].t) {
                ll id = par[v];
                edges[id].flow     += f;
                edges[id^1].flow   -= f;
                cost               += f * edges[id].cost;
            }

            flow += f;
        }
        return { flow, cost };
    }
};
