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

ll dfs(
    ll u,
    vector<ll> &par,
    vector<bool> &vis,
    vector<bool> &rec,
    vector<ll> &cyc
) {
    cyc.pb(u);
    if (rec[u]) {
        return u; 
    }
    if (vis[u]) {
        cyc.pop_back();
        return -1;
    }
    vis[u] = true;
    rec[u] = true;
    ll tmp = dfs(par[u], par, vis, rec, cyc);
    if (tmp != -1) {
        return tmp;
    }
    rec[u] = false;
    cyc.pop_back();
    return -1;
}

void prune_cyc(vector<ll> &cyc) {
    ll idx = 0;
    while (cyc[idx] != cyc.back()) {
        idx++;
    }
    cyc.erase(cyc.begin(), cyc.begin() + idx);
}

void dfs2(
    ll u,
    ll cyc_id,
    ll tree_id,
    vector<vector<ll>> &rev_adj,
    vector<vector<ll>> &type,
    ll &cnt,
    ll depth = 0
) {
    type[u][1] = cyc_id;
    type[u][2] = tree_id;
    type[u][3] = cnt++;
    type[u][5] = depth;
    FORE (v, rev_adj[u]) {
        if (type[v][0] == 1) {
            continue;
        }
        dfs2(v, cyc_id, tree_id, rev_adj, type, cnt, depth + 1);
    }
    type[u][4] = cnt++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<ll> par(n);
    vector<vector<ll>> rev_adj(n);
    FOR (i, n) {
        ll x;
        cin >> x;
        x--;
        par[i] = x;
        rev_adj[x].pb(i);
    }
    vector<ll> cyc_sz;
    // {cycle/tree?, cycle id, tree id, pre, post, depth, pos}
    vector<vector<ll>> type(n, vector<ll>(6));
    vector<bool> vis(n), rec(n);
    ll cyc_id = 0;
    FOR (i, n) {
        if (!vis[i]) {
            vector<ll> cyc;
            rec = vector<bool>(n);
            dfs(i, par, vis, rec, cyc);
            if (sz(cyc) == 0) {
                continue;
            }
            prune_cyc(cyc);
            ll idx = 0;
            FORE (u, cyc) {
                type[u] = {1, cyc_id, -1, -1, -1, -1, idx};
                idx++;
            }
            cyc_sz.pb(sz(cyc) - 1);
            cyc_id++;
        }
    }
    FOR (i, n) {
        if (type[i][0] == 1) {
            ll cnt = 0;
            dfs2(i, type[i][1], i, rev_adj, type, cnt);
        }
    }
    FOR (i, n) {
        cout << type[i][5] + cyc_sz[type[i][1]] << ' ';
    }

    return 0;
}