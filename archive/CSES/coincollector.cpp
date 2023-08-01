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
    stack<ll> st;

    SCCs(ll n0, vector<vector<ll>> &adj0) {
        n = n0, idx = 0, scc_cnt = 0;
        adj = adj0;
        ord = vector<ll>(n, -1);
        low = vector<ll>(n, -1);
        ids = vector<ll>(n, -1);
        on_stack = vector<bool>(n, false);
        FOR (u, n) {
            if (ord[u] == -1) {
                dfs(u);
            }
        }
        adj_scc = vector<vector<ll>>(scc_cnt);
        FOR (u, n) {
            FORE (v, adj[u]) {
                if (ids[u] != ids[v]) {
                    adj_scc[ids[u]].pb(ids[v]);
                }
            }
        }
    }

    void dfs(ll u) {
        ord[u] = low[u] = idx++;
        st.push(u);
        on_stack[u] = true;
        FORE (v, adj[u]) {
            if (ord[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } elif (on_stack[v]) {
                low[u] = min(low[u], ord[v]);
            }
        }
        if (low[u] == ord[u]) {
            while (true) {
                ll v = st.top();
                st.pop();
                ids[v] = scc_cnt;
                on_stack[v] = false;
                if (u == v) {
                    break;
                }
            }
            scc_cnt++;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<ll> val(n);
    FORE (x, val) {
        cin >> x;
    }
    vector<vector<ll>> adj(n);
    FOR (i, m) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
    }
    SCCs sccs(n, adj);
    vector<ll> scc_val(sccs.scc_cnt);
    FOR (i, n) {
        scc_val[sccs.ids[i]] += val[i];
    }
    vector<ll> scc_in(sccs.scc_cnt);
    FORE (u, sccs.adj_scc) {
        FORE (v, u) {
            scc_in[v]++;
        }
    }
    queue<ll> q;
    FOR (i, sccs.scc_cnt) {
        if (scc_in[i] == 0) {
            q.push(i);
        }
    }
    vector<ll> scc_ord;
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        scc_ord.pb(u);
        FORE (v, sccs.adj_scc[u]) {
            scc_in[v]--;
            if (scc_in[v] == 0) {
                q.push(v);
            }
        }
    }
    vector<ll> dp(sccs.scc_cnt);
    FORE (u, scc_ord) {
        dp[u] = scc_val[u];
    }
    FORE (u, scc_ord) {
        FORE (v, sccs.adj_scc[u]) {
            dp[v] = max(dp[v], dp[u] + scc_val[v]);
        }
    }
    cout << *max_element(all(dp)) << '\n';

    return 0;
}