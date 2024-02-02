#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

void dfs(ll u, ll p, vector<ll> &edges, vector<vector<ll>> &adj, vector<bool> &vis, vector<vector<ll>> &span, ll &back) {
    vis[u] = true;
    FORE (e, adj[u]) {
        ll v = edges[e];
        if (v == p) continue;
        if (v == 1) back = e;
        if (!vis[v]) {
            dfs(v, u, edges, adj, vis, span, back);
            span[u].pb(v);
        }
    }
}

struct LCA {
    vector<vector<ll>> parent, adj;
    vector<ll> pre, post, depth;
    ll n, timer;
    LCA(ll &n0, vector<vector<ll>> &adj0) {
        n = n0;
        timer = 0;
        pre = vector<ll>(n), post = pre, depth = pre;
        parent = vector<vector<ll>>(n, vector<ll>(30));
        adj = adj0; dfs(1, 1, 0); gen();
    }
    void dfs(ll node, ll par, ll d) {
        pre[node] = timer++;
        depth[node] = d;
        parent[node][0] = par;
        FORE (child, adj[node]) if (child != par) dfs(child, node, d + 1);
        post[node] = timer++;
    }
    void gen()
    { FOR (i, 29) FOR (j, n) parent[j][i + 1] = parent[parent[j][i]][i]; }
    bool is_anc(ll u, ll v) // is u an ancestor of v?
    { return pre[u] <= pre[v] && post[u] >= post[v]; }
    ll lca(ll u, ll v) {
        if (is_anc(u, v)) return u;
        if (is_anc(v, u)) return v;
        FORR (i, 30) if (!is_anc(parent[u][i], v)) u = parent[u][i];
        return parent[u][0];
    }
    ll dist(ll u, ll v)
    { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }
};

void move(LCA &lca, ll s, ll t, map<pair<ll, ll>, ll> &k_id, set<ll> &cur_ks, vector<pair<ll, vector<ll>>> &moves) {
    vector<ll> path;
    ll u;
    if (lca.is_anc(s, t)) {
        u = t;
        while (u != s) {
            path.pb(u);
            ll v = lca.parent[u][0];
            cur_ks.insert(k_id[{u, v}]);
            u = v;
        }
        path.pb(s);
        flip(path);
    } else {
        u = s;
        while (u != t) {
            path.pb(u);
            ll v = lca.parent[u][0];
            cur_ks.insert(k_id[{u, v}]);
            u = v;
        }
        path.pb(t);
    }
    FOB (i, 1, sz(path)) {
        moves.pb({0, {path[i]}});
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m; cin >> n >> m;
    ll back = -1;
    map<pair<ll, ll>, ll> k_id;
    vector<ll> edges;
    vector<vector<ll>> adj(n), span(n);
    FOR (i, m) {
        ll u, v; cin >> u >> v;
        edges.pb(u);
        edges.pb(v);
        adj[v].pb(2 * i);
        adj[u].pb(2 * i + 1);
        k_id[{u, v}] = i;
        k_id[{v, u}] = i;
    }
    vector<bool> vis(n);
    dfs(1, -1, edges, adj, vis, span, back);
    if (back == -1) {
        cout << "No solution\n";
        return 0;
    }
    ll x = edges[back ^ 1];
    LCA lca(n, span);
    set<ll> alice_k, bob_k;
    // {0, {x}}: move to x
    // {1, {k1, k2, ...}}: drop/grab keys k1, k2, ...
    vector<pair<ll, vector<ll>>> alice, bob;
    if (lca.is_anc(0, x)) {
        // alice: (0 -> 1 span)
        // bob: (1 -> x back) (x -> 0 span)

        // alice
        move(lca, 0, 1, k_id, alice_k, alice); // (0 -> 1 span)

        // bob
        bob.pb({0, {x}}); // (1 -> x back)
        bob_k.insert(k_id[{1, x}]);
        move(lca, x, 0, k_id, bob_k, bob); // (x -> 0 span)
    } elif (lca.lca(0, x) == 1) {
        // alice: (0 -> 1 span) (1 -> x span) [drops (0 -> 1 span)] (x -> 1 span)
        // bob: (1 -> x back) [takes (1 -> 0 span)] (x -> 1 back) (1 -> 0 span)

        set<ll> drop;

        // alice
        move(lca, 0, 1, k_id, drop, alice); // (0 -> 1 span)
        FORE (k, drop) alice_k.insert(k);
        move(lca, 1, x, k_id, alice_k, alice); // (1 -> x span)
        alice.pb({1, vector<ll>(all(drop))}); // [drops (0 -> 1 span)]
        move(lca, x, 1, k_id, alice_k, alice); // (x -> 1 span)

        // bob
        bob.pb({0, {x}}); // (1 -> x back)
        bob_k.insert(k_id[{1, x}]);
        bob.pb({1, {}}); // [takes (1 -> 0 span)]
        bob.pb({0, {1}}); // (x -> 1 back)
        move(lca, 1, 0, k_id, drop, bob); // (1 -> 0 span)
    } else {
        ll y = lca.lca(0, x);
        // alice: (0 -> y span) [drops (0 -> y span)] (y -> 1 span)
        // bob: (1 -> x back) (x -> y span) [takes (1 -> y span)] (y -> 0 span)

        set<ll> drop;

        // alice
        move(lca, 0, y, k_id, drop, alice); // (0 -> y span)
        FORE (k, drop) alice_k.insert(k);
        alice.pb({1, vector<ll>(all(drop))}); // [drops (0 -> y span)]
        move(lca, y, 1, k_id, alice_k, alice); // (y -> 1 span)

        // bob
        bob.pb({0, {x}}); // (1 -> x back)
        bob_k.insert(k_id[{1, x}]);
        move(lca, x, y, k_id, bob_k, bob); // (x -> y span)
        bob.pb({1, {}}); // [takes (1 -> y span)]
        move(lca, y, 0, k_id, drop, bob); // (y -> 0 span)
    }
    FORE (k, alice_k) {
        assert(!bob_k.count(k));
    }
    FORE (k, alice_k) cout << k << ' ';
    cout << '\n';
    FORE (k, bob_k) cout << k << ' ';
    cout << '\n';
    for (auto [m, vec] : alice) {
        if (m == 0) {
            assert(sz(vec) == 1);
            cout << "MOVE " << vec[0] << '\n';
        } else {
            cout << "DROP";
            FORE (k, vec) cout << ' ' << k;
            cout << '\n';
        }
    }
    cout << "DONE\n";
    for (auto [m, vec] : bob) {
        if (m == 0) {
            assert(sz(vec) == 1);
            cout << "MOVE " << vec[0] << '\n';
        } else {
            cout << "GRAB\n";
        }
    }
    cout << "DONE\n";

    return 0;
}