#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

#define sz(C) (ll) C.size()

const ll INF = 4e18;

// -----------------------------------------------------------------------------
//  Shortest paths
// -----------------------------------------------------------------------------
//  Supports:   - bellman_ford(n, edges, src)   negative edges ok   O(n m)
//              - dijkstra(n, adj, src)         weights >= 0        O(m log m)
//              - floyd_warshall(dist)          all pairs, neg ok   O(n^3)
//  Restrictions:
//              - INF marks unreachable throughout; dist + w must fit in ll
//  Notes:      - negative cycles: an extra bellman_ford relax pass changes
//                something iff one is reachable; after floyd_warshall,
//                dist[i][i] < 0 marks one
// -----------------------------------------------------------------------------

// edges = {a, b, w}, directed
vector<ll> bellman_ford(ll n, vector<tuple<ll, ll, ll>> &edges, ll src) {
    vector<ll> dist(n, INF);
    dist[src] = 0;
    for (ll i = 0; i < n - 1; i++)
        for (auto [a, b, w] : edges)
            if (dist[a] != INF && dist[a] + w < dist[b])
                dist[b] = dist[a] + w;
    return dist;
}

// adj[u] = {v, w}; std:: dodges pbds' priority_queue when that namespace is open
vector<ll> dijkstra(ll n, vector<vector<pll>> &adj, ll src) {
    vector<ll> dist(n, INF);
    dist[src] = 0;
    std::priority_queue<pll, vector<pll>, greater<>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }
    return dist;
}

// in place; seed dist[i][i] = 0, dist[a][b] = w, INF elsewhere
void floyd_warshall(vector<vector<ll>> &dist) {
    ll n = sz(dist);
    for (ll k = 0; k < n; k++)
        for (ll i = 0; i < n; i++)
            for (ll j = 0; j < n; j++)
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}
