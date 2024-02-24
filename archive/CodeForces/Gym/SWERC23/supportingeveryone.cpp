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

const ll INF = 1e18;

struct Edge { ll s, t, cap = 0, cost = 0, flow = 0; };

struct MinCostMaxFlow {
    ll n, m; vector<Edge> edges;
    vector<vector<ll>> adj;
    vector<ll> dist, pi, vis;
    vector<pll> par;

    MinCostMaxFlow(ll n, vector<Edge> &edges0) :
        n(n), m(sz(edges0)), adj(n),
        vis(n), dist(n), pi(n), par(n) {
        FORE (e, edges0) {
            adj[e.s].pb(sz(edges));
            edges.pb(e);
            adj[e.t].pb(sz(edges));
            edges.pb({e.t, e.s});
        }
    }

    void path(ll s) {
        vis.assign(n, false);
        dist.assign(n, INF);
        dist[s] = 0; ll di;

        __gnu_pbds::priority_queue<pll, greater<>> pq;
        vector<decltype(pq)::point_iterator> its(n);
        pq.push({0, s});

        auto relax = [&](ll t, ll e, ll cap, ll cost, ll dir) {
            ll val = di - pi[t] + cost;
            if (cap && val < dist[t]) {
                dist[t] = val;
                par[t] = {e, dir};
                if (its[t] == pq.end()) its[t] = pq.push({val, t});
                else pq.modify(its[t], {val, t});
            }
        };

        while (!pq.empty()) {
            s = pq.top().s; pq.pop();
            vis[s] = 1; di = dist[s] + pi[s];
            FORE (e, adj[s]) {
                ll t = edges[e].t;
                if (!vis[t]) relax(t, e, edges[e].cap - edges[e].flow, edges[e].cost, 1);
            }
            FORE (e, adj[s]) {
                ll t = edges[e].t;
                if (!vis[t]) relax(t, e, edges[e ^ 1].flow, -edges[e ^ 1].cost, 0);
            }
        }

        FOR (i, n) pi[i] = min(pi[i] + dist[i], INF);
    }

    pll max_flow(ll s, ll t) {
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
        FORE (e, edges) cost += e.flow * e.cost;
        return {flow, cost};
    }

    void set_pi(ll s) { // for negative costs
        pi.assign(n, INF); pi[s] = 0;
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