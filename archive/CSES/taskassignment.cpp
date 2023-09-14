#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

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

constexpr ll INF = 1e18;

struct Edge {
    ll s, t, cap = 0, cost = 0, flow = 0;
};

struct MinCostMaxFlow { // matrix
    ll n;
    vector<Edge> edges;
    vector<vector<ll>> adj, caps, flows, costs;
    vector<ll> vis, dist, pi;
    vector<pair<ll, ll>> par;
 
    MinCostMaxFlow(ll n, vector<Edge> &edges) :
        n(n), adj(n), edges(edges),
        caps(n, vector<ll>(n)),
        flows(n, vector<ll>(n)),
        costs(n, vector<ll>(n)),
        vis(n), dist(n), pi(n), par(n)
    {
        FORE (e, edges) {
            adj[e.s].pb(e.t);
            adj[e.t].pb(e.s);
            caps[e.s][e.t] = e.cap;
            costs[e.s][e.t] = e.cost;
        }
    }
 
    void path(ll s) {
        vis.assign(n, 0);
        dist.assign(n, INF);
        dist[s] = 0;
        ll di;
 
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
        pq.push({0, s});
        
        auto relax = [&](ll i, ll cap, ll cost, ll dir) {
            ll val = di - pi[i] + cost;
            if (cap && val < dist[i]) {
                dist[i] = val;
                par[i] = {s, dir};
                pq.push({dist[i], i});
            }
        };
 
        while (!pq.empty()) {
            s = pq.top().second;
            pq.pop();
            vis[s] = 1;
            di = dist[s] + pi[s];
            FORE (i, adj[s]) {
                if (!vis[i]) {
                    relax(i, caps[s][i] - flows[s][i], costs[s][i], 1);
                }
            }
            FORE (i, adj[s]) {
                if (!vis[i]) {
                    relax(i, flows[i][s], -costs[i][s], 0);
                }
            }
        }
 
        FOR (i, n) {
            pi[i] = min(pi[i] + dist[i], INF);
        }
    }
    
    pair<ll, ll> max_flow(ll s, ll t) {
        ll flow = 0, cost = 0;
        while (path(s), vis[t]) {
            ll fl = INF;
            for (ll p, r, x = t; tie(p, r) = par[x], x != s; x = p) {
                fl = min(fl, r ? caps[p][x] - flows[p][x] : flows[x][p]);
            }
            flow += fl;
            for (ll p, r, x = t; tie(p, r) = par[x], x != s; x = p) {
                if (r) flows[p][x] += fl;
                else flows[x][p] -= fl;
            }
        }
        FOR (i, n) {
            FOR (j, n) {
                cost += costs[i][j] * flows[i][j];
            }
        }
        return {flow, cost};
    }
 
    void set_pi(ll s) { // for negative costs
        pi.assign(n, INF);
        pi[s] = 0;
        ll it = n, ch = 1, v;
        while (ch-- && it--) {
            FOR (i, n) {
                if (pi[i] != INF) {
                    FORE (j, adj[i]) {
                        if (caps[i][j]) {
                            if ((v = pi[i] + costs[i][j]) < pi[j]) {
                                pi[j] = v;
                                ch = 1;
                            }
                        }
                    }
                }
            }
        }
        assert(it >= 0);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<Edge> edges;
    ll src = 2 * n, snk = 2 * n + 1;
    FOR (i, n) {
        FOR (j, n) {
            ll x;
            cin >> x;
            edges.pb({i, j + n, 1, x});
        }
    }
    FOR (i, n) {
        edges.pb({src, i, 1, 0});
        edges.pb({i + n, snk, 1, 0});
    }
    MinCostMaxFlow mcmf(2 * n + 2, edges);
    auto rv = mcmf.max_flow(src, snk);
    vector<pair<ll, ll>> used;
    FOR (i, n) {
        FORE (j, mcmf.adj[i]) {
            if (mcmf.flows[i][j] == 1) {
                used.pb({i, j - n});
            }
        }
    }
    cout << rv.second << '\n';
    FORE (x, used) {
        cout << x.first + 1 << ' ' << x.second + 1 << '\n';
    }

    return 0;
}