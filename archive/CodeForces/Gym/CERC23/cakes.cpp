#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef string str;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

struct Edge {
    ll s, t, cap = 0, cost = 0, flow = 0;
};

struct Dinic {
    ll n; vector<Edge> edges;
    vector<vector<ll>> adj;
    vector<ll> lvl, ptr;
    queue<ll> q;

    Dinic(ll n, vector<Edge> &edges0) :
        n(n), adj(n), lvl(n), ptr(n) {
        ll i = 0;
        for (auto e : edges0) {
            edges.pb(e);
            edges.pb({e.t, e.s});
            adj[e.s].pb(i++);
            adj[e.t].pb(i++);
        }
    }

    bool bfs(ll s, ll t) {
        lvl.assign(n, -1); lvl[s] = 0;
        q.push(s);
        while(!q.empty()) {
            ll v = q.front();
            q.pop();
            for (auto e : adj[v]) {
                ll u = edges[e].t;
                if (lvl[u] != -1 || edges[e].cap <= edges[e].flow) continue;
                lvl[u] = lvl[v] + 1;
                q.push(u);
            }
        }
        return lvl[t] != -1;
    }

    ll dfs(ll v, ll t, ll f) {
        if (v == t || f == 0) return f;
        for (ll &cid = ptr[v]; cid < sz(adj[v]); cid++) {
            ll e = adj[v][cid];
            ll u = edges[e].t;
            if (lvl[v] + 1 != lvl[u]) continue;
            ll pushed = dfs(u, t, min(f, edges[e].cap - edges[e].flow));
            if (pushed) {
                edges[e].flow += pushed;
                edges[e ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    ll max_flow(ll s, ll t) {
        ll flow = 0;
        while (bfs(s, t)) {
            ptr.assign(n, 0);
            while (ll pushed = dfs(s, t, __LONG_LONG_MAX__)) flow += pushed;
        }
        return flow;
    }
};

int main() {
    ll g, c, t;
    cin >> g >> c >> t;
    vector<ll> price_cake(c), price_ing(g), price_tool(t), profit_cake(c);
    FOR (i, c) cin >> price_cake[i];
    profit_cake = price_cake;
    FOR (i, g) cin >> price_ing[i];
    FOR (i, t) cin >> price_tool[i];
    FOR (i, c) FOR (j, g) {
        ll x; cin >> x;
        profit_cake[i] -= x * price_ing[j];
        if (profit_cake[i] < 0) profit_cake[i] = 0;
    }
    vector<Edge> edges;
    ll src = c + t, snk = src + 1;
    FOR (i, c) {
        edges.pb({src, i, profit_cake[i]});
    }
    FOR (i, c) {
        ll m; cin >> m;
        FOR (_, m) {
            ll cur_tool; cin >> cur_tool;
            cur_tool--;
            edges.pb({i, c + cur_tool, __LONG_LONG_MAX__});
        }
    }
    FOR (i, t) {
        edges.pb({c + i, snk, price_tool[i]});
    }
    Dinic dinic(snk + 1, edges);
    ll flow = dinic.max_flow(src, snk);
    ll tot = accumulate(all(profit_cake), 0LL);
    ll rv = tot - flow;
    cout << rv << '\n';
}