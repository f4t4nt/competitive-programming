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
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

ll MOD, pow10_[30];

ll pow10(ll x) {
    ll rv = 1;
    FOR (i, 30) {
        if (x & (1 << i)) {
            rv = (rv * pow10_[i]) % MOD;
        }
    }
    return rv;
}

struct LCA_Tree {
    vector<vector<ll>> parent, up, down;
    vector<ll> pre, post, depth;
    ll n, timer;

    LCA_Tree(vector<pair<ll, ll>> &edges, vector<ll> &values, ll root = 0) {
        n = 0;
        FORE (edge, edges) {
            n = max(n, edge.first + 1);
            n = max(n, edge.second + 1);
        }
        timer = 0;
        pre = vector<ll>(n);
        post = vector<ll>(n);
        depth = vector<ll>(n);
        parent = vector<vector<ll>>(n, vector<ll>(30));
        up = vector<vector<ll>>(n, vector<ll>(30));
        down = vector<vector<ll>>(n, vector<ll>(30));
        vector<vector<ll>> adj(n);
        FORE (edge, edges) {
            adj[edge.first].pb(edge.second);
            adj[edge.second].pb(edge.first);
        }
        dfs(adj, root, 0);
        generate();
        FOR (i, n) {
            up[i][0] = values[i];
            down[i][0] = values[i];
        }
        FOR (i, 29) {
            FOR (j, n) {
                up[j][i + 1] = (up[j][i] * pow10_[i] + up[parent[j][i]][i]) % MOD;
                down[j][i + 1] = (down[j][i] + down[parent[j][i]][i] * pow10_[i]) % MOD;
            }
        }
    }

    void generate(ll root = 0) {
        FOR (i, 29) {
            FOR (j, n) {
                parent[j][i + 1] = parent[parent[j][i]][i];
            }
        }
    }

    void dfs(vector<vector<ll>> &adj, ll node, ll par, ll d = 0) {
        pre[node] = timer++;
        parent[node][0] = par;
        depth[node] = d;
        FORE (child, adj[node]) {
            if (child != par) {
                dfs(adj, child, node, d + 1);
            }
        }
        post[node] = timer++;
    }

    bool is_ancestor(ll u, ll v) {
        return pre[u] <= pre[v] && post[u] >= post[v];
    }

    ll get_up(ll v, ll k) {
        ll rv = 0;
        FOR (i, 30) {
            if (k & (1 << i)) {
                rv = (rv * pow10_[i] + up[v][i]) % MOD;
                v = parent[v][i];
            }
        }
        return rv;
    }

    ll get_down(ll v, ll k) {
        ll rv = 0, len = 0;
        FOR (i, 30) {
            if (k & (1 << i)) {
                rv = (rv + down[v][i] * pow10(len)) % MOD;
                v = parent[v][i];
                len += (1 << i);
            }
        }
        return rv;
    }

    ll lca(ll u, ll v) {
        if (is_ancestor(u, v)) {
            return get_down(v, depth[v] - depth[u] + 1);
        }
        if (is_ancestor(v, u)) {
            return get_up(u, depth[u] - depth[v] + 1);
        }
        ll old_u = u;
        FORR (i, 30) {
            if (!is_ancestor(parent[u][i], v)) {
                u = parent[u][i];
            }
        }
        ll up_part = get_up(old_u, depth[old_u] - depth[parent[u][0]] + 1);
        ll down_part = get_down(v, depth[v] - depth[parent[u][0]]);
        return (up_part * pow10(depth[v] - depth[parent[u][0]]) + down_part) % MOD;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> MOD >> q;

    pow10_[0] = 10;
    FOR (i, 29) {
        pow10_[i + 1] = (pow10_[i] * pow10_[i]) % MOD;
    }

    vector<pair<ll, ll>> edges(n - 1);
    FOR (i, n - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        edges[i] = mp(u, v);
    }
    vector<ll> values(n);
    FOR (i, n) {
        cin >> values[i];
    }
    LCA_Tree lca(edges, values);
    
    while(q--) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        cout << lca.lca(a, b) << '\n';
    }

    return 0;
}