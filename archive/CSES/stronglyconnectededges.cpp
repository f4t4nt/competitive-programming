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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll n, m;
    cin >> n >> m;
    set<pair<ll, ll>> rv;
    vector<vector<ll>> adj(n);
    FOR(i, m) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<bool> vis(n);
    vector<ll> tin(n), low(n);
    ll timer = 0;
    bool ok = true;
    auto dfs = [&](auto &&self, ll u, ll p) -> void {
        vis[u] = true;
        tin[u] = low[u] = timer++;
        FORE (v, adj[u]) {
            if (v == p) {
                continue;
            }
            if (!rv.count({v, u})) {
                rv.insert({u, v});
            }
            if (vis[v]) {
                low[u] = min(low[u], tin[v]);
            } else {
                self(self, v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u]) {
                    ok = false;
                }
            }
            if (!ok) {
                return;
            }
        }
    };
    dfs(dfs, 0, -1);
    if (!ok) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    ok = true;
    FOR(i, n) {
        if (!vis[i]) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        cout << "IMPOSSIBLE\n";
    } else {
        FORE (p, rv) {
            cout << p.first + 1 << ' ' << p.second + 1 << '\n';
        }
    }

    return 0;
}