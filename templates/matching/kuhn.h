#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Kuhn: maximum matching in a bipartite graph
// - LHS nodes: 0 .. nL-1
// - RHS nodes: 0 .. nR-1
// - adj[u]   : list of neighbours of u in LHS
// Worst case time complexity: O(E * V)
struct Kuhn {
    ll nL, nR;
    vector<vector<ll>> &adj;        // external adjacency (avoids copy)

    vector<ll> match_l, match_r;    // LHS→RHS, RHS→LHS (-1 = free)
    vector<ll> seen;                // visitation timestamp array
    ll iter = 1;                    // current DFS stamp
    ll matched = 0;                 // size of current matching

    Kuhn(vector<vector<ll>> &_adj,
                     ll _nL, ll _nR)
        : nL(_nL), nR(_nR), adj(_adj),
          match_l(nL, -1), match_r(nR, -1),
          seen(nR, 0) {}

    bool dfs(ll u) {
        for (ll v : adj[u]) if (seen[v] != iter) {
            seen[v] = iter;
            if (match_r[v] == -1 || dfs(match_r[v])) {
                match_l[u] = v;
                match_r[v] = u;
                return true;
            }
        }
        return false;
    }

    ll solve() {
        // greedy pre-matching
        for (ll u = 0; u < nL; u++) if (match_l[u] == -1) {
            for (ll v : adj[u]) if (match_r[v] == -1) {
                match_l[u] = v;
                match_r[v] = u;
                matched++;
                break;
            }
        }
        // augment until no path found
        for (ll u = 0; u < nL; u++) if (match_l[u] == -1) {
            iter++;
            if (dfs(u)) matched++;
            if (matched == min(nL, nR)) break;  // perfect -> done
        }
        return matched;
    }
};
