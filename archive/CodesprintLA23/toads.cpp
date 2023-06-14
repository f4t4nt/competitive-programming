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

// https://codesprintla23.kattis.com/problems/codesprintla23.toads

constexpr ll INF = 1e15;

struct DSU {
    ll cnt;
    vector<ll> e;
    DSU() {}
    DSU(ll n) { e = vector<ll>(n, -1); cnt = n; }
    void reset() { e = vector<ll>(sz(e), -1); cnt = sz(e); }
    ll get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool same_set(ll a, ll b) { return get(a) == get(b); }
    ll size(ll x) { return -e[get(x)]; }
    ll count() { return cnt; }
    bool unite(ll x, ll y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y]; e[y] = x;
        cnt--;
        return true;
    }
};

struct LCA_Tree {
    DSU &dsu;
    vector<vector<ll>> parent;
    vector<vector<pair<ll, ll>>> adj;
    vector<ll> pre, post, depth;
    ll n, timer;

    LCA_Tree(ll &n0, vector<unordered_map<ll, ll>> &adj0, DSU &dsu0) : dsu(dsu0) {
        n = n0;
        timer = 0;
        pre = vector<ll>(n), post = pre, depth = pre;
        parent = vector<vector<ll>>(n, vector<ll>(30));
        adj = vector<vector<pair<ll, ll>>>(n);
        FOR (i, n) {
            FORE (child, adj0[i]) {
                if (child.first < i) continue;
                adj[i].pb({child.first, child.second});
                adj[child.first].pb({i, child.second});
            }
        }
        ll idx = 0;
        while (idx < n) {
            if (pre[idx] == 0) {
                dfs(idx, idx, 0);
            }
            idx++;
        }
        gen();
    }

    void dfs(ll node, ll par, ll d) {
        pre[node] = timer++;
        depth[node] = d;
        parent[node][0] = par;
        FORE (child, adj[node]) {
            if (child.first != par) {
                dfs(child.first, node, d + child.second);
            }
        }
        post[node] = timer++;
    }

    void gen() {
        FOR (i, 29) {
            FOR (j, n) {
                parent[j][i + 1] = parent[parent[j][i]][i];
            }
        }
    }

    bool is_anc(ll u, ll v) {
        return pre[u] <= pre[v] && post[u] >= post[v];
    }

    ll lca(ll u, ll v) {
        if (is_anc(u, v)) return u;
        if (is_anc(v, u)) return v;
        FORR (i, 30) {
            if (!is_anc(parent[u][i], v)) {
                u = parent[u][i];
            }
        }
        return parent[u][0];
    }

    ll dist(ll u, ll v) {
        if (!dsu.same_set(u, v)) {
            return INF;
        } else {
            return depth[u] + depth[v] - 2 * depth[lca(u, v)];
        }
    }
};

vector<tuple<ll, ll, ll>> inv_mst(ll n, vector<tuple<ll, ll, ll>> &edges, DSU &dsu) {
    vector<tuple<ll, ll, ll>> rv;
    ssort(edges);
    FORE (edge, edges) {
        ll d, u, v;
        tie(d, u, v) = edge;
        if (!dsu.unite(u, v)) {
            rv.pb(edge);
        }
    }
    return rv;
}

unordered_map<ll, ll> djikstra(ll n, vector<unordered_map<ll, ll>> &adj, ll s) {
    unordered_map<ll, ll> dist;
    dist[s] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        ll d, u;
        tie(d, u) = pq.top();
        pq.pop();
        if (dist.count(u) && d > dist[u]) continue;
        FORE (child, adj[u]) {
            ll v, w;
            tie(v, w) = child;
            if (!dist.count(v) || dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, q;
    cin >> n;
    vector<unordered_map<ll, ll>> adj(n);
    FOR (u, n) {
        ll v, d;
        cin >> v >> d;
        v--;
        if (adj[u].count(v)) {
            adj[u][v] = min(adj[u][v], d);
        } else {
            adj[u][v] = d;
        }
        adj[v][u] = adj[u][v];
    }
    cin >> m;
    FOR (i, m) {
        ll u, v, d;
        cin >> u >> v >> d;
        u--, v--;
        if (adj[u].count(v)) {
            adj[u][v] = min(adj[u][v], d);
        } else {
            adj[u][v] = d;
        }
        adj[v][u] = adj[u][v];
    }
    vector<tuple<ll, ll, ll>> edges;
    FOR (i, n) {
        FORE (child, adj[i]) {
            if (child.first < i) continue;
            edges.pb({child.second, i, child.first});
        }
    }
    DSU dsu(n);
    auto xtra = inv_mst(n, edges, dsu);
    vector<unordered_map<ll, ll>> xtra_dists;
    vector<vector<ll>> idxs(n);
    FORE (edge, xtra) {
        ll d, u, v;
        tie(d, u, v) = edge;
        xtra_dists.pb(djikstra(n, adj, u));
        FORE (v, xtra_dists.back()) {
            idxs[v.first].pb(sz(xtra_dists) - 1);
        }
    }
    FORE (edge, xtra) {
        ll d, u, v;
        tie(d, u, v) = edge;
        adj[u].erase(v);
        adj[v].erase(u);
    }
    LCA_Tree lca(n, adj, dsu);
    cin >> q;
    while (q--) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        ll rv = lca.dist(a, b);
        if (rv == INF) {
            rv = -1;
        } else {
            FORE (idx, idxs[a]) {
                if (xtra_dists[idx].count(b)) {
                    rv = min(rv, xtra_dists[idx][a] + xtra_dists[idx][b]);
                }
            }
        }
        cout << rv << '\n';
    }

    return 0;
}