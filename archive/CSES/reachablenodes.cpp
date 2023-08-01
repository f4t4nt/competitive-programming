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

#pragma GCC target("popcnt")

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

void dfs(ll u, vector<vector<ll>> &adj, vector<bitset<50000>> &dp, vector<bool> &vis) {
    vis[u] = true;
    FORE (v, adj[u]) {
        if (!vis[v]) {
            dfs(v, adj, dp, vis);
        }
        dp[u] |= dp[v];
    }
    dp[u][u] = 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n);
    FOR (i, m) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        adj[a].pb(b);
    }
    vector<bitset<50000>> dp(n);
    vector<bool> vis(n);
    FOR (i, n) {
        if (!vis[i]) {
            dfs(i, adj, dp, vis);
        }
    }
    FOR (i, n) {
        cout << dp[i].count() << ' ';
    }
    cout << '\n';

    return 0;
}