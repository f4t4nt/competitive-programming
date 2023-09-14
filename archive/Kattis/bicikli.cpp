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

constexpr ll MOD = 1e9;

void dfs(ll u, vector<vector<ll>> &adj, vector<bool> &vis) {
    vis[u] = true;
    FORE(v, adj[u]) {
        if (!vis[v]) {
            dfs(v, adj, vis);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<ll> in(n);
    vector<vector<ll>> adj(n), adjr(n);
    FOR(i, m) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adjr[v].pb(u);
    }
    vector<bool> vis(n), visr(n);
    set<ll> s;
    dfs(0, adj, vis);
    dfs(1, adjr, visr);
    ll cnt = 0;
    FOR(i, n) {
        if (vis[i] && visr[i]) {
            cnt++;
        }
    }
    FOR (i, n) {
        if (vis[i] && visr[i]) {
            FORE(v, adj[i]) {
                if (vis[v] && visr[v]) {
                    in[v]++;
                }
            }
        }
    }
    vector<ll> top_sort;
    queue<ll> q;
    FOR(i, n) {
        if (in[i] == 0 && vis[i] && visr[i]) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        top_sort.pb(u);
        FORE(v, adj[u]) {
            in[v]--;
            if (in[v] == 0 && vis[v] && visr[v]) {
                q.push(v);
            }
        }
    }
    if (sz(top_sort) != cnt) {
        cout << "inf\n";
        return 0;
    }
    vector<pair<bool, ll>> dp(n);
    dp[0] = {false, 1};
    FORE(u, top_sort) {
        FORE(v, adj[u]) {
            if (dp[u].first) {
                dp[v].first = true;
            }
            dp[v].second += dp[u].second;
            if (dp[v].second >= MOD) {
                dp[v].first = true;
            }
            dp[v].second %= MOD;
        }
    }
    if (dp[1].first) {
        cout << setw(9) << setfill('0');
    }
    cout << dp[1].second << '\n';

    return 0;
}