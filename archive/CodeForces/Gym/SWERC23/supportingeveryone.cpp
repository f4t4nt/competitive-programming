#include <bits/stdc++.h>

using namespace std;

// typedef long long ll;
typedef int ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll INF = 1e9;

struct Edge { ll s, t, cap = 0, cost = 0, flow = 0; };

struct MinCostMaxFlow {
    ll n;                       // number of vertices
    vector<Edge> edges;         // both directions (reverse cost = –cost)
    vector<vector<ll>> adj;     // adjacency (edge indices)

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

    // Bellman–Ford to initialise Johnson potentials if negative costs exist
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m; cin >> n >> m;
    vector<Edge> edges;
    ll src = n + m, snk = n + m + 1;
    FOR (i, m) edges.pb({src, i, 1, 1});
    FOR (i, n) edges.pb({i + m, snk, 1, 0});
    FOR (i, n) {
        ll cnt; cin >> cnt;
        FOR (j, cnt) {
            ll k; cin >> k; k--;
            edges.pb({k, i + m, 1, 0});
        }
    }
    MinCostMaxFlow mcmf(snk + 1, edges);
    auto [flow, cost] = mcmf.max_flow(src, snk);
    cout << cost << '\n';

    return 0;
}