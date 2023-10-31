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

// imma show YOU how great i am.

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    FOR (i, n) cin >> a[i];
    vector<vector<ll>> adj(n);
    FOR (i, n - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<ll> siz(n), add(n);
    ll rv = 0;
    auto dfs1 = [&](auto &&self, ll u, ll p) -> void {
        siz[u] = 1;
        FORE (v, adj[u]) {
            if (v != p) {
                self(self, v, u);
                siz[u] += siz[v];
                rv += siz[v] * (a[u] ^ a[v]);
                add[v] += (n - 2 * siz[v]) * (a[u] ^ a[v]);
            }
        }
    };
    dfs1(dfs1, 0, -1);
    auto dfs2 = [&](auto &&self, ll u, ll p) -> void {
        FORE (v, adj[u]) {
            if (v != p) {
                add[v] += add[u];
                self(self, v, u);
            }
        }
    };
    dfs2(dfs2, 0, -1);
    FOR (i, n) {
        cout << rv + add[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}