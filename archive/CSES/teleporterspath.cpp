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

void dfs(ll u, vector<vector<ll>> &adj, vector<ll> &rv) {
    while (sz(adj[u])) {
        ll v = adj[u].back();
        adj[u].pop_back();
        dfs(v, adj, rv);
    }
    rv.pb(u);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<ll> in(n);
    vector<vector<ll>> adj(n);
    FOR (i, m) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        in[v]++;
    }
    ll cnt = 0;
    FOR (i, n) {
        if (in[i] == sz(adj[i])) {
            cnt++;
        }
    }
    if (cnt != n - 2 || in[0] + 1 != sz(adj[0]) || in[n - 1] != sz(adj[n - 1]) + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    vector<ll> rv;
    dfs(0, adj, rv);
    if (sz(rv) != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    FORR (i, sz(rv)) {
        cout << rv[i] + 1 << ' ';
    }
    cout << '\n';

    return 0;
}