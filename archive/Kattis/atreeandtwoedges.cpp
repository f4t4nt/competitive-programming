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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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
    vector<vector<ll>> parent, adj;
    vector<ll> pre, post, depth;
    ll n, timer;

    LCA_Tree(ll &n0, vector<vector<ll>> &adj0) {
        n = n0;
        timer = 0;
        pre = vector<ll>(n), post = pre, depth = pre;
        parent = vector<vector<ll>>(n, vector<ll>(30));
        adj = adj0;
        dfs(0, 0, 0);
        gen();
    }

    void dfs(ll node, ll par, ll d) {
        pre[node] = timer++;
        depth[node] = d;
        parent[node][0] = par;
        FORE (child, adj[node]) {
            if (child != par) {
                dfs(child, node, d + 1);
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
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    bool disjoint(vector<pair<ll, ll>> paths) {
        vector<pair<ll, ll>> p;
        FORE (path, paths) {
            ll u, v;
            tie(u, v) = path;
            ll w = lca(u, v);
            p.pb({w, u});
            p.pb({w, v});
        }
        FOR (i, sz(p)) {
            FOR (j, i - i % 2) {
                if (!(lca(p[i].second, p[j].first) != p[j].first ||
                    lca(p[j].second, p[i].first) != p[i].first))
                {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> special_edges;
    vector<vector<ll>> adj(n);
    DSU dsu(n);
    FOR (i, n + 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        if (dsu.same_set(u, v)) {
            special_edges.pb({u, v});
        } else {
            dsu.unite(u, v);
            adj[u].pb(v);
            adj[v].pb(u);
        }
    }
    ll &a = special_edges[0].first, &b = special_edges[0].second,
        &c = special_edges[1].first, &d = special_edges[1].second;
    LCA_Tree lca(n, adj);
    while (q--) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        ll rv = 1 + 
            lca.disjoint({{u, a}, {b, v}}) +
            lca.disjoint({{u, b}, {a, v}}) +
            lca.disjoint({{u, c}, {d, v}}) +
            lca.disjoint({{u, d}, {c, v}}) +
            lca.disjoint({{u, a}, {b, c}, {d, v}}) +
            lca.disjoint({{u, a}, {b, d}, {c, v}}) +
            lca.disjoint({{u, b}, {a, c}, {d, v}}) +
            lca.disjoint({{u, b}, {a, d}, {c, v}}) +
            lca.disjoint({{u, c}, {d, a}, {b, v}}) +
            lca.disjoint({{u, c}, {d, b}, {a, v}}) +
            lca.disjoint({{u, d}, {c, a}, {b, v}}) +
            lca.disjoint({{u, d}, {c, b}, {a, v}});
        cout << rv << '\n';
    }

    return 0;
}