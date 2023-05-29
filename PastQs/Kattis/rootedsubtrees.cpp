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

struct LCA_Tree {
    vector<vector<ll>> parent, adj;
    vector<ll> pre, post, depth;
    ll n, timer;

    LCA_Tree(ll &n0, vector<pair<ll, ll>> &edges) {
        n = n0;
        timer = 0;
        pre = vector<ll>(n), post = pre, depth = pre;
        parent = vector<vector<ll>>(n, vector<ll>(30));
        adj = vector<vector<ll>>(n);
        FORE (edge, edges) {
            adj[edge.first].pb(edge.second);
            adj[edge.second].pb(edge.first);
        }
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
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> edges(n - 1);
    FORE (e, edges) {
        cin >> e.first >> e.second;
        e.first--, e.second--;
    }
    LCA_Tree lca(n, edges);
    while (q--) {
        ll r, p;
        cin >> r >> p;
        r--, p--;
        ll x = lca.dist(r, p) + 1;
        cout << n - x + x * (x + 1) / 2 << '\n';
    }

    return 0;
}