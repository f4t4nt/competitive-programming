#include <bits/stdc++.h>
using namespace std;

typedef __int128 i128;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
// s.order_of_key(x) -> number of elements < x
// s.find_by_order(x) -> iterator to the x-th element (0-indexed)

#pragma GCC target("popcnt,lzcnt")
// __builtin_popcount(x) -> number of set bits
// __builtin_clz(x) -> number of leading zeros
// for ll, use __builtin_popcountll, __builtin_clzll

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define f first
// #define s second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

struct Bridges {
    ll n;                       // |V|
    vector<vector<ll>> &adj;    // external adjacency
    vector<ll> tin, low;        // discovery time & low-link
    vector<bool> vis;           // DFS visited
    ll timer = 0;               // global DFS timer
    vector<pll> bridges;        // output list

    explicit Bridges(ll _n, vector<vector<ll>> &_adj)
        : n(_n), adj(_adj),
          tin(n, -1), low(n, -1), vis(n, false) {}

    vector<pll> solve() {
        for (ll v = 0; v < n; v++)
            if (!vis[v]) dfs(v, -1);
        return bridges;
    }

private:
    void add_bridge(ll u, ll v) {
        if (u > v) swap(u, v);
        bridges.pb({u, v});
    }

    void dfs(ll v, ll p) {
        vis[v] = true;
        tin[v] = low[v] = timer++;

        bool parent_skipped = false;            // skip only one copy of the parent edge
        for (ll to : adj[v]) {
            if (to == p && !parent_skipped) {   // ignore the edge we came from
                parent_skipped = true;
                continue;
            }

            if (vis[to]) {                      // back-edge
                low[v] = min(low[v], tin[to]);
            } else {                            // tree-edge
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] > tin[v])           // no back-edge from subtree
                    add_bridge(v, to);
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m; cin >> n >> m;
    vector<vector<ll>> adj(n);
    for (ll i = 0; i < m; i++) {
        ll u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    Bridges br(n, adj);
    auto bridges = br.solve();
    cout << sz(bridges) << '\n';
    for (auto [u, v] : bridges)
        cout << u + 1 << ' ' << v + 1 << '\n';

    return 0;
}
