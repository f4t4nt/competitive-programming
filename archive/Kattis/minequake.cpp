#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
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
// #define f first
// #define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

void solve(vector<vector<ll>> &adj, vector<ll> &sum_dist, vector<bool> &vis, ll v, ll &cur, ll &tot) {
    vis[v] = true;
    tot += cur;
    vector<ll> ord = adj[v];
    sort(all(ord), [&](ll u, ll w) { return sum_dist[u] > sum_dist[w]; });
    for (ll &u : ord) {
        if (vis[u]) continue;
        cur++;
        solve(adj, sum_dist, vis, u, cur, tot);
    }
    cur++;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    // vector<vector<ll>> adj(n, vector<ll>(n, 1e18));
    // FOR (i, n - 1) {
    //     ll u, v; cin >> u >> v;
    //     u--, v--;
    //     adj[u][v] = adj[v][u] = 1;
    // }
    // FOR (i, n) adj[i][i] = 0;
    // FOR (k, n) FOR (i, n) FOR (j, n) adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
    // vector<ll> perm(n);
    // iota(all(perm), 0);
    // ll ans = 1e18;
    // do {
    //     ll tot = 0, cur = 0, v = perm[0];
    //     for (ll u : perm) {
    //         cur += adj[v][u];
    //         tot += cur;
    //         v = u;
    //     }
    //     ans = min(ans, tot);
    // } while (next_permutation(all(perm)));
    // cout << ans << '\n';

    vector<ll> parent(n), subtree_sz(n), sum_dist(n), depth(n);
    vector<vector<ll>> adj(n), children(n);
    FOR (i, n - 1) {
        ll u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    auto dfs0 = [&](auto &&self, ll v, ll p) -> void {
        parent[v] = p;
        subtree_sz[v] = 1;
        if (p != -1) depth[v] = depth[p] + 1;
        for (ll &u : adj[v]) {
            if (u == p) continue;
            children[v].pb(u);
            self(self, u, v);
            subtree_sz[v] += subtree_sz[u];
        }
    };
    dfs0(dfs0, 0, -1);
    sum_dist[0] = accumulate(all(depth), 0LL);
    auto dfs1 = [&](auto &&self, ll v) -> void {
        for (ll &u : children[v]) {
            sum_dist[u] = sum_dist[v] + n - 2 * subtree_sz[u];
            self(self, u);
        }
    };
    dfs1(dfs1, 0);
    ll rt = 0;
    FOR (i, n) if (sum_dist[i] > sum_dist[rt]) rt = i;
    parent = vector<ll>(n);
    subtree_sz = vector<ll>(n);
    depth = vector<ll>(n);
    children = vector<vector<ll>>(n);
    dfs0(dfs0, rt, -1);
    vector<bool> vis(n);
    ll cur = 0, tot = 0;
    solve(children, sum_dist, vis, rt, cur, tot);
    cout << tot << '\n';

    return 0;
}