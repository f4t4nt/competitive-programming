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
    ll,
    null_type,
    less<ll>,
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
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
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

struct SCCs {
    ll n, idx, scc_cnt;
    vector<vector<ll>> adj;
    vector<set<ll>> adj_scc; // [0]: snk, [-1]: src
    vector<ll> ord, low, ids;
    vector<bitset<50000>> dp;
    vector<bool> on_stack;
    stack<ll> stk;

    SCCs(ll n0, vector<vector<ll>> &adj0) {
        n = n0, idx = 0, scc_cnt = 0;
        adj = adj0;
        ord = vector<ll>(n, -1);
        low = vector<ll>(n, -1);
        ids = vector<ll>(n, -1);
        on_stack = vector<bool>(n, false);
        FOR (u, n) if (ord[u] == -1) dfs(u);
        adj_scc = vector<set<ll>>(scc_cnt);
        FOR (u, n) for (ll v : adj[u]) if (ids[u] != ids[v]) {
            adj_scc[ids[u]].insert(ids[v]);
        }
        vector<bool> vis(scc_cnt, false);
        dp = vector<bitset<50000>>(scc_cnt);
        FOR (u, scc_cnt) if (!vis[u]) dfs2(u, vis);
    }

    void dfs2(ll u, vector<bool> &vis) {
        vis[u] = true;
        for (ll v : adj_scc[u]) {
            if (!vis[v]) dfs2(v, vis);
            dp[u] |= dp[v];
        }
        dp[u][u] = 1;
    }

    bool u_to_v(ll u, ll v) {
        u = ids[u], v = ids[v];
        return dp[u][v];
    }

    void dfs(ll u) {
        ord[u] = low[u] = idx++;
        stk.push(u);
        on_stack[u] = true;
        for (ll v : adj[u]) {
            if (ord[v] == -1) dfs(v), low[u] = min(low[u], low[v]);
            elif (on_stack[v]) low[u] = min(low[u], ord[v]);
        }
        if (low[u] == ord[u]) {
            while (true) {
                ll v = stk.top();
                stk.pop();
                ids[v] = scc_cnt;
                on_stack[v] = false;
                if (u == v) break;
            }
            scc_cnt++;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
 
    ll n, m, q;
    cin >> n >> m >> q;
    vector<vector<ll>> adj(n);
    FOR (i, m) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
    }
    // vector<bitset<50000>> dp(n);
    // FOR (i, n) dp[i][i] = 1;
    // FOR (k, 16) FOR (i, n) for (ll j : adj[i]) dp[i] |= dp[j];
    // while (q--) {
    //     ll a, b;
    //     cin >> a >> b;
    //     a--; b--;
    //     cout << (dp[a][b] ? "YES" : "NO") << '\n';
    // }
    SCCs scc(n, adj);
    while (q--) {
        ll a, b; cin >> a >> b; a--, b--;
        cout << (scc.u_to_v(a, b) ? "YES" : "NO") << '\n';
    }
 
    return 0;
}