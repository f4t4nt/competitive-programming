#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Hopcroft-Karp: maximum matching in a bipartite graph
// - LHS nodes: 0 .. nL-1
// - RHS nodes: 0 .. nR-1
// - adj[u]   : list of neighbours of u in LHS
// Worst case time complexity: O(E * sqrt(V))
struct HopcroftKarp {
    ll nL, nR;
    vector<vector<ll>> &adj;        // external adjacency (avoids copy)

    vector<ll> match_l, match_r;    // LHS -> RHS, RHS -> LHS (-1 = free)
    vector<ll> dist;                // BFS levels
    queue<ll> q;

    explicit HopcroftKarp(vector<vector<ll>> &_adj,
                          ll _nL, ll _nR)
        : nL(_nL), nR(_nR), adj(_adj),
          match_l(nL, -1), match_r(nR, -1),
          dist(nL) {}

    // BFS builds alternating-level graph; returns true if free RHS reachable
    bool bfs() {
        while (!q.empty()) q.pop();
        for (ll u = 0; u < nL; u++) {
            if (match_l[u] == -1) dist[u] = 0, q.push(u);
            else                  dist[u] = -1;
        }
        bool reachable = false;
        while (!q.empty()) {
            ll u = q.front(); q.pop();
            for (ll v : adj[u]) {
                ll nxt = match_r[v];
                if (nxt != -1 && dist[nxt] == -1) {
                    dist[nxt] = dist[u] + 1;
                    q.push(nxt);
                }
                if (nxt == -1) reachable = true;    // an unmatched RHS exists
            }
        }
        return reachable;
    }

    // DFS searches for augmenting paths within BFS levels
    bool dfs(ll u) {
        for (ll v : adj[u]) {
            ll nxt = match_r[v];
            if (nxt == -1 || (dist[nxt] == dist[u] + 1 && dfs(nxt))) {
                match_l[u] = v;
                match_r[v] = u;
                return true;
            }
        }
        dist[u] = -1;   // block useless nodes
        return false;
    }

    ll solve() {
        ll matched = 0;
        // optional greedy pre-match (improves running time in dense graphs)
        for (ll u = 0; u < nL; u++) if (match_l[u] == -1)
            for (ll v : adj[u]) if (match_r[v] == -1) {
                match_l[u] = v;
                match_r[v] = u;
                matched++; break;
            }

        // Hopcroft-Karp phases
        while (bfs()) {
            for (ll u = 0; u < nL; u++)
                if (match_l[u] == -1 && dfs(u))
                    matched++;
            if (matched == min(nL, nR)) break;   // perfect ⇒ done
        }
        return matched;
    }
};
