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
        auto a0 = dfs(0, -1, adj0);
        auto a1 = dfs(0, -1, adj1);
        cout << (a0 == a1 ? "YES" : "NO") << '\n';
    }

    return 0;
}