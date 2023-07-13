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

ll dx[] = {1, 0, 0, -1, 0, 0};
ll dy[] = {0, 1, 0, 0, -1, 0};
ll dz[] = {0, 0, 1, 0, 0, -1};

constexpr ll INF = 1e18;
constexpr ll MAXD = 10;
constexpr ll MAXN = 1e3;

struct Edge {
    ll s, t, cap = 0, cost = 0, flow = 0;
};

struct Dinic { // edge list
    ll n;
    vector<Edge> edges;
    vector<vector<ll>> adj;
    vector<ll> lvl, ptr;
    queue<ll> q;

    Dinic(ll n, vector<Edge> &edges0) :
        n(n), adj(n), lvl(n), ptr(n) {
        ll i = 0;
        FORE (e, edges0) {
            edges.pb(e);
            edges.pb({e.t, e.s});
            adj[e.s].pb(i++);
            adj[e.t].pb(i++);
        }
    }

    bool bfs(ll s, ll t) {
        lvl.assign(n, -1);
        lvl[s] = 0;
        q.push(s);
        while (!q.empty()) {
            ll v = q.front();
            q.pop();
            FORE (e, adj[v]) {
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
            while (ll pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }

    vector<pair<ll, ll>> min_cut(ll s) {
        bfs(s, n - 1);
        vector<pair<ll, ll>> cut;
        FORE (e,edges) {
            if (lvl[e.s] != -1 && lvl[e.t] == -1 && e.cap > 0) {
                cut.pb({e.s, e.t});
            }
        }
        return cut;
    }

    void undo_flow(vector<ll> path, ll f) {
        FOR (i, sz(path) - 1) {
            FORE (e, adj[path[i]]) {
                if (edges[e].t == path[i + 1]) {
                    edges[e].flow -= f;
                    edges[e ^ 1].flow += f;
                    assert(edges[e].flow <= edges[e].cap);
                    assert(edges[e ^ 1].flow <= edges[e ^ 1].cap);
                    break;
                }
            }
        }
    }
};

ll get_cap(ll i) {
    vector<ll> pt = {i / 100, (i / 10) % 10, i % 10};
    ll cap = 0;
    FOR (j, 3) {
        if (pt[j] == 0 || pt[j] == MAXD - 1) {
            cap++;
        }
    }
    return cap;
}

vector<ll> get_adj(ll i) {
    vector<ll> pt = {i / 100, (i / 10) % 10, i % 10};
    vector<ll> adj;
    FOR (j, 6) {
        vector<ll> pt2 = pt;
        pt2[0] += dx[j];
        pt2[1] += dy[j];
        pt2[2] += dz[j];
        if (pt2[0] < 0 || pt2[0] >= MAXD) continue;
        if (pt2[1] < 0 || pt2[1] >= MAXD) continue;
        if (pt2[2] < 0 || pt2[2] >= MAXD) continue;
        adj.pb(pt2[0] * 100 + pt2[1] * 10 + pt2[2]);
    }
    return adj;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, src = MAXN, snk = MAXN + 1;
    cin >> n;
    vector<bool> pts(MAXN);
    FOR (i, n) {
        ll x, y, z;
        cin >> x >> y >> z;
        pts[x * 100 + y * 10 + z] = true;
    }
    vector<Edge> edges;
    FOR (i, MAXN) {
        ll cap = get_cap(i);
        if (cap > 0) {
            edges.pb({src, i, cap});
        }
    }
    FOR (i, MAXN) {
        vector<ll> adj = get_adj(i);
        FORE (j, adj) {
            edges.pb({i, j, 1});
        }
        if (pts[i]) {
            edges.pb({i, snk, 6});
        }
    }
    Dinic dinic(MAXN + 2, edges);
    ll flow = dinic.max_flow(src, snk);
    cout << flow << '\n';

    return 0;
}