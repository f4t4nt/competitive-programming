#include <bits/stdc++.h>

using namespace std;

using ll = long long;
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

constexpr ll INF = 1e18;

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
        vis(n), dist(n), pi(n), par(n)
    {
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

    void set_pi(ll s) { // for negative costs, untested
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

    str t;
    cin >> t;
    vector<vector<ll>> reft(26);
    FOR (i, sz(t)) {
        reft[t[i] - 'a'].pb(i);
    }
    ll n;
    cin >> n;
    vector<pair<str, ll>> s(n);
    FOR (i, n) {
        cin >> s[i].first >> s[i].second;
    }
    // [0, n) - source words
    // [n, n + sz(t)) - target
    // [n + sz(t), n + sz(t) + cnt) - source letters
    // n + sz(t) + cnt - source
    // n + sz(t) + cnt + 1 - target
    ll cnt = 0;
    vector<Edge> edges;
    FOR (i, n) {
        FORE (c, s[i].first) {
            edges.pb({i, n + sz(t) + cnt, 1, 0});
            FORE (j, reft[c - 'a']) {
                edges.pb({n + sz(t) + cnt, n + j, 1, i + 1});
            }
            cnt++;
        }
    }
    ll source = n + sz(t) + cnt, target = source + 1;
    FOR (i, sz(t)) {
        edges.pb({n + i, target, 1, 0});
    }
    FOR (i, n) {
        edges.pb({source, i, s[i].second, 0});
    }
    MinCostMaxFlow f(target + 1, edges);
    ll flow, rv;
    tie(flow, rv) = f.max_flow(source, target);
    if (flow == sz(t)) {
        cout << rv << '\n';
    } else {
        cout << -1 << '\n';
    }

    return 0;
}