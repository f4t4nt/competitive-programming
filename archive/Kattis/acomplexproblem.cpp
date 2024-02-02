#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
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
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

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

struct SCCs {
    ll n, idx, scc_cnt;
    vector<vector<ll>> adj, adj_scc;
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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll m, n; cin >> m >> n;
    map<str, ll> ids;
    vector<str> names;
    vector<tuple<ll, ll, ll>> edges;
    FOR (i, m) {
        str A, B; cin >> A >> B;
        if (ids.find(A) == ids.end()) ids[A] = sz(ids), names.pb(A);
        if (ids.find(B) == ids.end()) ids[B] = sz(ids), names.pb(B);
        edges.pb({ids[A], ids[B], 0});
    }
    FOR (i, n) {
        str A, B; cin >> A >> B;
        if (ids.find(A) == ids.end()) ids[A] = sz(ids), names.pb(A);
        if (ids.find(B) == ids.end()) ids[B] = sz(ids), names.pb(B);
        edges.pb({ids[A], ids[B], 1});
    }
    ll N = sz(ids);
    vector<vector<ll>> adj(N);
    for (auto [u, v, w] : edges) adj[u].pb(v);
    SCCs sccs(N, adj);
    map<pair<ll, ll>, ll> ws;
    for (auto [u, v, w] : edges) {
        ws[{sccs.ids[u], sccs.ids[v]}] = w;
    }
    ll mn = 0, mx = sccs.scc_cnt;
    assert(sz(sccs.adj_scc[0]) == 0);
    vector<ll> dp(sccs.scc_cnt, 1);
    FORR (i, sccs.scc_cnt) {
        FORE (j, sccs.adj_scc[i]) {
            dp[j] = max(dp[j], dp[i] + ws[{i, j}]);
        }
    }
    mn = *max_element(all(dp));
    cout << mn << ' ' << mx << '\n';

    return 0;
}