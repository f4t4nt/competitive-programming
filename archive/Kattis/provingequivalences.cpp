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
#define x first
#define y second

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

struct SCCs {
    ll n, idx, scc_cnt;
    vector<vector<ll>> adj,
        adj_scc; // [0]: snk, [-1]: src
    vector<ll> ord, low, ids;
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
        adj_scc = vector<vector<ll>>(scc_cnt);
        FOR (u, n) FORE (v, adj[u]) if (ids[u] != ids[v]) {
            adj_scc[ids[u]].pb(ids[v]);
        }
    }

    void dfs(ll u) {
        ord[u] = low[u] = idx++;
        stk.push(u);
        on_stack[u] = true;
        FORE (v, adj[u]) {
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

    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        vector<vector<ll>> adj(n);
        FOR(i, m) {
            ll u, v; cin >> u >> v;
            u--, v--;
            adj[u].pb(v);
        }
        SCCs scc(n, adj);
        if (scc.scc_cnt == 1) {
            cout << 0 << '\n';
            continue;
        }
        vector<ll> in(scc.scc_cnt), out(scc.scc_cnt);
        FOR (i, scc.scc_cnt) FORE (j, scc.adj_scc[i]) {
            in[j]++;
            out[i]++;
        }
        ll in0 = 0, out0 = 0;
        FOR (i, scc.scc_cnt) {
            if (!in[i]) in0++;
            if (!out[i]) out0++;
        }
        cout << max(in0, out0) << '\n';
    }

    return 0;
}