#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

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

ll dfs(ll u, LCA_Tree &tree, vector<ll> &del, vector<ll> &rv) {
    rv[u] = del[u];
    FORE (v, tree.adj[u]) {
        if (v != tree.parent[u][0]) {
            rv[u] += dfs(v, tree, del, rv);
        }
    }
    return rv[u];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n);
    FOR (i, n - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    LCA_Tree tree(n, adj);
    vector<ll> del(n), rv(n);
    vector<pair<ll, ll>> paths(m);
    FORE (path, paths) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        path = {u, v};
        del[u]++;
        del[v]++;
        ll lca = tree.lca(u, v);
        del[lca]--;
        if (lca != 0) {
            del[tree.parent[lca][0]]--;
        }
    }
    dfs(0, tree, del, rv);
    FORE (x, rv) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}