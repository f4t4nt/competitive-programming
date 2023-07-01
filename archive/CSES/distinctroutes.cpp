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

struct Edge {
    ll s, t, cap, cost;
};

struct Dinic { 
    ll n, m = 0;
    vector<vector<ll>> adj, caps, flows;
    vector<set<ll>> outs;
    vector<ll> lvl, ptr;
    queue<ll> q;

    Dinic(ll n, vector<Edge> &edges) :
        n(n), adj(n),
        caps(n, vector<ll>(n)),
        flows(n, vector<ll>(n)),
        outs(n)
    {
        FORE (e, edges) {
            adj[e.s].pb(e.t);
            adj[e.t].pb(e.s);
            caps[e.s][e.t] = e.cap;
        }
    }

    bool bfs(ll s, ll t) {
        lvl.assign(n, -1);
        lvl[s] = 0;
        q.push(s);
        while (!q.empty()) {
            ll v = q.front();
            q.pop();
            FORE (u, adj[v]) {
                if (lvl[u] != -1 || caps[v][u] <= flows[v][u]) {
                    continue;
                }
                lvl[u] = lvl[v] + 1;
                q.push(u);
            }
        }
        return lvl[t] != -1;
    }

    ll dfs(ll v, ll t, ll f) {
        if (v == t || f == 0) {
            return f;
        }
        for (ll &cid = ptr[v]; cid < sz(adj[v]); cid++) {
            ll u = adj[v][cid];
            if (lvl[v] + 1 != lvl[u] || caps[v][u] <= flows[v][u]) {
                continue;
            }
            ll tr = dfs(u, t, min(f, caps[v][u] - flows[v][u]));
            if (caps[v][u] == 0) {
                outs[u].erase(v);
            } else {
                outs[v].insert(u);
            }
            if (tr == 0) {
                if (caps[v][u] == 0) {
                    outs[u].insert(v);
                } else {
                    outs[v].erase(u);
                }
                continue;
            }
            flows[v][u] += tr;
            flows[u][v] -= tr;
            return tr;
        }
        return 0;
    }

    ll max_flow(ll s, ll t) {
        flows.assign(n, vector<ll>(n));
        ll flow = 0;
        while (true) {
            if (!bfs(s, t)) {
                break;
            }
            ptr.assign(n, 0);
            while (ll pushed = dfs(s, t, LLONG_MAX)) {
                flow += pushed;
            }
        }
        return flow;
    }

    void dfs2(ll v, vector<ll> &path) {
        if (v == n - 1) {
            return;
        }
        FORE (u, outs[v]) {
            if (flows[v][u] > 0) {
                path.pb(u);
                dfs2(u, path);
                return;
            }
        }
    }

    void get_paths(vector<vector<ll>> &paths) {
        while (!outs[0].empty()) {
            vector<ll> path = {0};
            dfs2(0, path);
            FOR (i, sz(path) - 1) {
                outs[path[i]].erase(path[i + 1]);
            }
            paths.pb(path);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<Edge> edges;
    FOR (i, m) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        edges.pb({a, b, 1});
    }
    Dinic dinic(n, edges);
    ll flow = dinic.max_flow(0, n - 1);
    cout << flow << '\n';
    vector<vector<ll>> paths;
    dinic.get_paths(paths);
    assert(sz(paths) == flow);
    FORE (path, paths) {
        cout << sz(path) << '\n';
        FORE (v, path) {
            cout << v + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}