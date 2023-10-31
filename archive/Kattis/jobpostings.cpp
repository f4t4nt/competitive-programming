#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
#include <bits/extc++.h>
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

// imma show YOU how great i am.

const ll INF = 1e18;

struct Edge {
    ll s, t, cap = 0, cost = 0, flow = 0;
};

struct MinCostMaxFlow {
    ll n, m;
    vector<Edge> edges;
    vector<vector<ll>> adj;
    vector<ll> dist, pi, vis;
    vector<pair<ll, ll>> par;

    MinCostMaxFlow(ll n, vector<Edge> &edges0) :
        n(n), m(sz(edges0)), adj(n),
        vis(n), dist(n), pi(n), par(n) {
        ll i = 0;
        FORE (e, edges0) {
            edges.pb(e);
            edges.pb({e.t, e.s});
            adj[e.s].pb(i++);
            adj[e.t].pb(i++);
        }
    }

    void path(ll s) {
        vis.assign(n, false);
        dist.assign(n, INF);
        dist[s] = 0;
        ll di;

        __gnu_pbds::priority_queue<pair<ll, ll>, greater<>> pq;
        vector<decltype(pq)::point_iterator> its(n);
        pq.push({0, s});

        auto relax = [&](ll t, ll e, ll cap, ll cost, ll dir) {
            ll val = di - pi[t] + cost;
            if (cap && val < dist[t]) {
                dist[t] = val;
                par[t] = {e, dir};
                if (its[t] == pq.end()) {
                    its[t] = pq.push({val, t});
                } else {
                    pq.modify(its[t], {val, t});
                }
            }
        };

        while (!pq.empty()) {
            s = pq.top().second;
            pq.pop();
            vis[s] = 1;
            di = dist[s] + pi[s];
            FORE (e, adj[s]) {
                ll t = edges[e].t;
                if (!vis[t]) {
                    relax(t, e, edges[e].cap - edges[e].flow, edges[e].cost, 1);
                }
            }
            FORE (e, adj[s]) {
                ll t = edges[e].t;
                if (!vis[t]) {
                    relax(t, e, edges[e ^ 1].flow, -edges[e ^ 1].cost, 0);
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
            ll f = INF;
            for (ll p, r, x = t; tie(p, r) = par[x], x != s; x = edges[p].s) {
                f = min(f, r ? edges[p].cap - edges[p].flow : edges[p ^ 1].flow);
            }
            flow += f;
            for (ll p, r, x = t; tie(p, r) = par[x], x != s; x = edges[p].s) {
                if (r) edges[p].flow += f;
                else edges[p ^ 1].flow -= f;
            }
        }
        FORE (e, edges) {
            cost += e.flow * e.cost;
        }
        return {flow, cost};
    }

    void set_pi(ll s) { // for negative costs
        pi.assign(n, INF);
        pi[s] = 0;
        ll it = n, ch = 1, v;
        while (ch-- && it--) {
            FOR (i, n) {
                if (pi[i] == INF) continue;
                FORE (e, adj[i]) {
                    if (edges[e].cap && (v = pi[i] + edges[e].cost) < pi[edges[e].t]) {
                        pi[edges[e].t] = v;
                        ch = 1;
                    }
                }
            }
        }
        assert(it >= 0);
    }
};

ll matrix[3][4] = {
    { 4,  3,  2, 1},
    { 8,  7,  6, 5},
    {12, 11, 10, 9}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    while (cin >> n >> m && n) {
        vector<Edge> edges;
        // [0, n) postings
        // [n, n + m) students
        // n + m source
        // n + m + 1 sink
        ll src = n + m, snk = n + m + 1;
        // each student must select one
        FOR (i, m) {
            edges.pb({src, n + i, 1});
        }
        // posting availability
        FOR (i, n) {
            ll p; cin >> p;
            edges.pb({i, snk, p});
        }
        // student preference
        FOR (i, m) {
            ll j; cin >> j; j--;
            FOR (k, 4) {
                ll c; cin >> c;
                edges.pb({n + i, c, 1, -matrix[j][k]});
            }
        }
        MinCostMaxFlow mcmf(snk + 1, edges);
        mcmf.set_pi(src);
        auto [flow, cost] = mcmf.max_flow(src, snk);
        assert(flow == m);
        cout << -cost << '\n';
    }

    return 0;
}