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
    vector<vector<ll>> parent;
    vector<vector<pair<ll, ll>>> adj;
    DSU dsu;
    vector<ll> pre, post, depth;
    ll n, timer;

    LCA_Tree(ll &n0, DSU &dsu0, vector<vector<pair<ll, ll>>> &adj0) {
        n = n0;
        dsu = dsu0;
        timer = 0;
        pre = vector<ll>(n), post = pre, depth = pre;
        parent = vector<vector<ll>>(n, vector<ll>(30));
        adj = adj0;
        FOR (root, n) {
            if (depth[root] == 0) {
                dfs(root, root, 0);
            }
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
        if (dsu.same_set(u, v)) {
            return depth[u] + depth[v] - 2 * depth[lca(u, v)];
        } else {
            return 1e18;
        }
    }
};

unordered_map<ll, ll> dijkstra(ll s, vector<vector<pair<ll, ll>>> &adj) {
    unordered_map<ll, ll> dist;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        ll d, u;
        tie(d, u) = pq.top();
        pq.pop();
        if (d > dist[u]) {
            continue;
        }
        FORE (elem, adj[u]) {
            ll v, w;
            tie(v, w) = elem;
            if (dist.find(v) == dist.end()) {
                dist[v] = 1e18;
            }
            if (dist[v] > dist[u] + w) {
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
    DSU dsu(n);
    vector<vector<pair<ll, ll>>> adj(n);
    vector<tuple<ll, ll, ll>> spec_edges;
    FOR (u, n) {
        ll v, d;
        cin >> v >> d;
        v--;
        if (!dsu.same_set(u, v)) {
            dsu.unite(u, v);
            adj[u].pb({v, d});
            adj[v].pb({u, d});
        } else {
            spec_edges.pb({u, v, d});
        }
    }
    LCA_Tree lca(n, dsu, adj);
    cin >> m;
    FOR (i, m) {
        ll u, v, d;
        cin >> u >> v >> d;
        u--, v--;
        spec_edges.pb({u, v, d});
        dsu.unite(u, v);
    }
    FORE (e, spec_edges) {
        adj[get<0>(e)].pb({get<1>(e), get<2>(e)});
        adj[get<1>(e)].pb({get<0>(e), get<2>(e)});
    }
    set<ll> spec_nodes;
    FORE (edge, spec_edges) {
        spec_nodes.insert(get<0>(edge));
    }
    unordered_map<ll, unordered_map<ll, ll>> spec_dists;
    FORE (u, spec_nodes) {
        spec_dists[u] = dijkstra(u, adj);
    }
    cin >> q;
    while (q--) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        if (!dsu.same_set(a, b)) {
            cout << -1 << '\n';
        } else {
            ll rv = lca.dist(a, b);
            FORE (elem, spec_dists) {
                auto &dist = elem.second;
                if (dist.find(a) == dist.end() ||
                    dist.find(b) == dist.end())
                {
                    continue;
                }
                rv = min(rv, dist[a] + dist[b]);
            }
            // FORE (e, spec_edges) {
            //     auto dists = dijkstra(get<0>(e), adj);
            //     rv = min(rv, dists[a] + dists[b]);
            // }
            if (rv == 1e18) {
                cout << -1 << '\n';
            } else {
                cout << rv << '\n';
            }
        }
    }

    return 0;
}