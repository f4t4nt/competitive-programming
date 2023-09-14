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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

constexpr ll MOD = 1e9 + 7;

ll pow2[200001];

// {len, hash}
pair<ll, ll> dfs(ll u, ll p, vector<vector<ll>> &adj) {
    pair<ll, ll> rv = {2, 1};
    vector<pair<ll, ll>> c;
    FORE (v, adj[u]) {
        if (v != p) {
            auto x = dfs(v, u, adj);
            c.pb(x);
        }
    }
    ssort(c);
    FORE (e, c) {
        rv.first += e.first;
        rv.second = (rv.second * pow2[e.first] + e.second) % MOD;
    }
    rv.second = (rv.second * 2) % MOD;
    return rv;
}

ll dfs(ll u, vector<vector<ll>> &adj, vector<ll> &par, vector<ll> &subtree_sz) {
    subtree_sz[u] = 1;
    FORE (v, adj[u]) {
        if (v != par[u]) {
            par[v] = u;
            subtree_sz[u] += dfs(v, adj, par, subtree_sz);
        }
    }
    return subtree_sz[u];
}

vector<ll> centroids(ll &n, vector<vector<ll>> &adj) {
    vector<ll> rv, par(n, -1), subtree_sz(n);
    dfs(0, adj, par, subtree_sz);
    FOR (i, n) {
        bool ok = true;
        ok &= (n - subtree_sz[i]) <= n / 2;
        FORE (v, adj[i]) {
            if (v != par[i]) {
                ok &= subtree_sz[v] <= n / 2;
            }
        }
        if (ok) {
            rv.pb(i);
        }
    }
    assert(sz(rv) == 1 || sz(rv) == 2);
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    pow2[0] = 1;
    FOB (i, 1, 200001) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }

    ll t, tmp = 0;
    cin >> t;
    while (t--) {
        tmp++;
        ll n;
        cin >> n;
        vector<vector<ll>> adj0(n), adj1(n);
        FOR (i, n - 1) {
            ll u, v;
            cin >> u >> v;
            u--, v--;
            adj0[u].pb(v);
            adj0[v].pb(u);
        }
        FOR (i, n - 1) {
            ll u, v;
            cin >> u >> v;
            u--, v--;
            adj1[u].pb(v);
            adj1[v].pb(u);
        }
        auto c0 = centroids(n, adj0),   
            c1 = centroids(n, adj1);
        auto a0 = dfs(c0[0], -1, adj0),
            a1 = dfs(c1[0], -1, adj1);
        if (a0 != a1 && sz(c0) == 2) {
            a0 = dfs(c0[1], -1, adj0);
        }
        cout << (a0 == a1 ? "YES" : "NO") << '\n';
    }

    return 0;
}