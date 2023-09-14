#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

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

ll dfs1(ll u, ll &r, vector<vector<ll>> &adj, vector<ll> &par, vector<ll> &root, vector<ll> &depth, vector<ll> &max_depth, vector<ll> &diameter) {
    root[u] = r;
    vector<ll> radii;
    FORE (v, adj[u]) {
        if (v != par[u]) {
            par[v] = u;
            depth[v] = depth[u] + 1;
            radii.pb(dfs1(v, r, adj, par, root, depth, max_depth, diameter));
        }
    }
    if (sz(radii)) {
        rsort(radii);
        max_depth[u] = radii[0];
        if (sz(radii) > 1) {
            diameter[u] = radii[0] + radii[1];
        } else {
            diameter[u] = radii[0];
        }
    }
    return max_depth[u] + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n);
    FOR(i, m) {
        ll u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<ll> par(n, -1), root(n), depth(n), max_depth(n), diameter(n), radius(n);
    FOR (i, n) {
        if (par[i] == -1) {
            dfs1(i, i, adj, par, root, depth, max_depth, diameter);
        }
    }
    ll rv = 0;
    FOR (i, n) {
        ll r = root[i], dia = diameter[i];
        diameter[i] = -1;
        diameter[r] = max(diameter[r], dia);
        rv = max(rv, diameter[r]);
    }
    vector<ll> radii;
    FOR (i, n) {
        if (diameter[i] != -1) {
            radii.pb((diameter[i] + 1) / 2);
        }
    }
    rsort(radii);
    if (sz(radii) > 1) {
        rv = max(rv, radii[0] + radii[1] + 1);
    }
    if (sz(radii) > 2) {
        rv = max(rv, radii[1] + radii[2] + 2);
    }
    cout << rv << '\n';

    return 0;
}