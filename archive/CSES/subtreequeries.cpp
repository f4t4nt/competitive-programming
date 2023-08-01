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

struct BIT {
    vector<ll> tree;
    ll n;
    BIT(ll n) : n(n) {
        tree.resize(n + 1);
    }
    void update(ll idx, ll val) {
        idx++;
        while (idx <= n) {
            tree[idx] += val;
            idx += idx & (-idx);
        }
    }
    ll query(ll idx) {
        idx++;
        ll sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & (-idx);
        }
        return sum;
    }
    ll query(ll l, ll r) {
        return query(r) - query(l - 1);
    }
};

void dfs(ll u, ll p, vector<vector<ll>> &adj, vector<ll> &in, vector<ll> &out, ll &timer) {
    in[u] = timer++;
    FORE (v, adj[u]) {
        if (v != p) {
            dfs(v, u, adj, in, out, timer);
        }
    }
    out[u] = timer++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, q;
    cin >> n >> q;
    vector<ll> vals(n);
    FORE (x, vals) {
        cin >> x;
    }
    vector<vector<ll>> adj(n);
    FOR (i, n - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<ll> in(n), out(n);
    ll timer = 0;
    dfs(0, -1, adj, in, out, timer);
    BIT bit(2 * n);
    FOR (i, n) {
        bit.update(out[i], vals[i]);
    }
    while (q--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll s, x;
            cin >> s >> x;
            s--;
            bit.update(out[s], x - vals[s]);
            vals[s] = x;
        } else {
            ll s;
            cin >> s;
            s--;
            cout << bit.query(in[s], out[s]) << '\n';
        }
    }

    return 0;
}