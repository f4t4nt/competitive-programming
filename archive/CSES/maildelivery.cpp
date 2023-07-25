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

void dfs(ll u, vector<ll> &path, vector<set<ll>> &adj) {
    while (sz(adj[u])) {
        ll v = *adj[u].rbegin();
        adj[u].erase(v);
        adj[v].erase(u);
        dfs(v, path, adj);
    }
    path.pb(u);
    return;
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
        u--; v--;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    bool ok = true;
    FOR (u, n) {
        if (sz(adj[u]) % 2) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    vector<ll> path;
    dfs(0, path, adj);
    if (sz(path) != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    FORE (u, path) {
        cout << u + 1 << ' ';
    }
    cout << '\n';
 
    return 0;
}