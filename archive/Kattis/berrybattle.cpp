#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
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
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, mx = 0; cin >> n;
    vector<vector<ll>> adj(n);
    FOR (i, n - 1) {
        ll u, v; cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
        mx = max(mx, max(sz(adj[u]), sz(adj[v])));
    }
    if (mx == n - 1) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    ll u = -1;
    FOR (i, n) if (sz(adj[i]) == 1) {
        u = i;
        break;
    }
    ll v = adj[u][0];
    cout << v + 1 << ' ' << u + 1;
    vector<bool> vis(n);
    vis[u] = vis[v] = true;
    auto dfs = [&](auto &&f, ll u) -> void {
        FORE (v, adj[u]) if (!vis[v]) {
            vis[v] = true;
            cout << ' ' << v + 1;
            f(f, v);
        }
    };
    dfs(dfs, v);
    cout << '\n';

    return 0;
}