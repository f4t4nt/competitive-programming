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

set<ll> dfs(ll u, ll p, vector<vector<ll>> &adj, vector<ll> &c, vector<ll> &rv) {
    set<ll> s;
    FORE (v, adj[u]) {
        if (v != p) {
            set<ll> t = dfs(v, u, adj, c, rv);
            if (sz(t) > sz(s)) {
                swap(s, t);
            }
            FORE (x, t) {
                s.insert(x);
            }
        }
    }
    s.insert(c[u]);
    rv[u] = sz(s);
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<ll> c(n), rv(n);
    FORE (ci, c) {
        cin >> ci;
    }
    vector<vector<ll>> adj(n);
    FOR (i, n - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(0, -1, adj, c, rv);
    FORE (x, rv) {
        cout << x << ' ';
    }

    return 0;
}