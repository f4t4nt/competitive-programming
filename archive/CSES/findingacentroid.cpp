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

ll dfs(ll u, vector<vector<ll>> &adj, vector<ll> &par, vector<ll> &subtree_sz) {
    subtree_sz[u] = 1;
    FORE (v, adj[u]) {
        if (v != par[u]) {
            par[v] = u;
            subtree_sz[u] += dfs(v, adj, par, subtree_sz);
        }
    }
    return subtree_sz[u];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<vector<ll>> adj(n);
    FOR (i, n - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<ll> par(n, -1), subtree_sz(n);
    dfs(0, adj, par, subtree_sz);
    FOR (i, n) {
        bool ok = true;
        ok &= (n - subtree_sz[i]) <= n / 2;
        FORE (v, adj[i]) {
            if (v != par[i]) {
                ok &= subtree_sz[v] <= n / 2;
            }
        }
        if (ok) {
            cout << i + 1 << '\n';
            return 0;
        }
    }

    return 0;
}