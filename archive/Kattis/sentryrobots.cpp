#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

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

void print_grid(vector<str> &g) {
    FORE (line, g) {
        cout << line << '\n';
    }
    cout << "---\n";
}

vector<str> expand(ll &x, ll &y, vector<str> &g) {
    vector<str> rv;
    FOR (i, y) {
        str line = "";
        FOR (j, x) {
            line += g[i][j];
            if (g[i][j] == '#') {
                ll cur_sz = sz(line);
                line += str(x - j - 1, '.');
                rv.pb(line);
                line = str(cur_sz, '.');
            }
        }
        if (sz(line) > 0) {
            rv.pb(line);
        }
    }
    return rv;
}

vector<str> rotate(ll &x, ll &y, vector<str> &g) {
    vector<str> rv;
    FOR (i, x) {
        str line = "";
        FOR (j, y) {
            line += g[j][i];
        }
        rv.pb(line);
    }
    return rv;
}

constexpr ll INF = 1e18;

struct Edge {
    ll s, t, cap = 0, cost = 0, flow = 0;
};

struct MinCostMaxFlow { // edge list
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

        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
        pq.push({0, s});

        auto relax = [&](ll t, ll e, ll cap, ll cost, ll dir) {
            ll val = di - pi[t] + cost;
            if (cap && val < dist[t]) {
                dist[t] = val;
                par[t] = {e, dir};
                pq.push({val, t});
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll y, x, p, w;
        cin >> y >> x >> p;
        vector<str> g0(y, str(x, '.')), g1, g2;
        while (p--) {
            ll py, px;
            cin >> py >> px;
            g0[py - 1][px - 1] = '*';
        }
        cin >> w;
        while (w--) {
            ll wy, wx;
            cin >> wy >> wx;
            g0[wy - 1][wx - 1] = '#';
        }
        // print_grid(g0);
        g1 = expand(x, y, g0);
        y = sz(g1), x = sz(g1[0]);
        // print_grid(g1);
        g1 = rotate(x, y, g1);
        y = sz(g1), x = sz(g1[0]);
        // print_grid(g1);
        g2 = expand(x, y, g1);
        y = sz(g2), x = sz(g2[0]);
        // print_grid(g2);
        FOR (i, y) {
            FOR (j, x) {
                if (g2[i][j] == '#') {
                    g2[i][j] = '.';
                }
            }
        }
        ll src = x + y, sink = src + 1;
        vector<Edge> edges;
        FOR (i, y) {
            edges.pb({src, i, 1, 0});
        }
        FOR (i, y) {
            FOR (j, x) {
                if (g2[i][j] == '*') {
                    edges.pb({i, j + y, 1, 1});
                }
            }
        }
        FOR (i, x) {
            edges.pb({i + y, sink, 1, 0});
        }
        MinCostMaxFlow mcmf(sink + 1, edges);
        auto [flow, cost] = mcmf.max_flow(src, sink);
        cout << cost << '\n';
    }

    return 0;
}