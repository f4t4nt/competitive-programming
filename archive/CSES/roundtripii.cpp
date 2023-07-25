#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
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
    vector<set<ll>> &adj,
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
    FORE (v, adj[u]) {
        ll tmp = dfs(v, adj, vis, rec, cyc);
        if (tmp != -1) {
            return tmp;
        }
    }
    rec[u] = false;
    cyc.pop_back();
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<set<ll>> adj(n);
    FOR (i, m) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].insert(v);
    }
    vector<bool> vis(n), rec(n);
    vector<ll> cyc;
    ll res = -1;
    FOR (i, n) {
        if (!vis[i]) {
            res = dfs(i, adj, vis, rec, cyc);
            if (res != -1) {
                break;
            }
        }
    }
    if (res == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        ll idx = 0;
        while (cyc[idx] != res) {
            idx++;
        }
        cyc.erase(cyc.begin(), cyc.begin() + idx);
        cout << sz(cyc) << '\n';
        FORE (u, cyc) {
            cout << u + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}