#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define pb push_back
#define sz(C) (ll) C.size()

const ll INF = 4e18;

// -----------------------------------------------------------------------------
//  Hungarian Min Cost Assignment (potentials, e-maxx style)
// -----------------------------------------------------------------------------
//  Supports:   - solve()      total cost of the optimal full assignment
//              - job[w]       job assigned to worker w, -1 = free
//              - min_cost[j]  optimal total using only jobs 0..j
//  Restrictions: - costs[j][w] held by reference; nJ <= nW, transpose
//                or pad otherwise
//  Complexity: O(J W^2)
// -----------------------------------------------------------------------------
struct Hungarian {
    ll nJ, nW;
    vector<vector<ll>> &costs;      // external cost matrix (avoids copy)

    vector<ll> job;                 // worker -> job; index nW is a virtual free worker
    vector<ll> ys, yt;              // job / worker potentials
    vector<ll> min_cost;            // min_cost[j] = best total over jobs 0..j

    Hungarian(vector<vector<ll>> &_costs)
        : nJ(sz(_costs)), nW(sz(_costs[0])), costs(_costs),
          job(nW + 1, -1), ys(nJ), yt(nW + 1) {}

    ll solve() {
        for (ll j_cur = 0; j_cur < nJ; j_cur++) {
            // dijkstra-like phase: grow Z from the virtual worker until a free one
            ll w_cur = nW;
            job[w_cur] = j_cur;
            vector<ll> min_to(nW + 1, INF), prv(nW + 1, -1);
            vector<bool> in_Z(nW + 1, false);
            while (job[w_cur] != -1) {
                in_Z[w_cur] = true;
                ll j = job[w_cur], del = INF, w_nxt = -1;
                for (ll w = 0; w < nW; w++) if (!in_Z[w]) {
                    if (min_to[w] > costs[j][w] - ys[j] - yt[w]) {
                        min_to[w] = costs[j][w] - ys[j] - yt[w];
                        prv[w] = w_cur;
                    }
                    if (del > min_to[w]) del = min_to[w], w_nxt = w;
                }
                for (ll w = 0; w <= nW; w++) {
                    if (in_Z[w]) ys[job[w]] += del, yt[w] -= del;
                    else min_to[w] -= del;
                }
                w_cur = w_nxt;
            }
            // walk back the augmenting path
            for (ll w; w_cur != nW; w_cur = w) job[w_cur] = job[w = prv[w_cur]];
            min_cost.pb(-yt[nW]);
        }
        return min_cost.back();
    }
};
