#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> ids, ok(n);
    map<ll, ll> id_mp;
    vector<vector<ll>> adj(n), inv_adj(n);
    FOR (i, n) {
        ll id, m;
        cin >> id >> m;
        ids.pb(id);
        id_mp[id] = i;
        FOR (j, m) {
            ll v;
            cin >> v;
            adj[i].pb(v);
        }
    }
    FOR (i, n) {
        FORE (v, adj[i]) {
            v = id_mp[v];
            inv_adj[v].pb(i);
        }
    }
    auto dfs = [&](auto &&self, ll u, vector<vector<ll>> &tmp, ll x) -> void {
        ok[u] |= x;
        FORE (v, tmp[u]) if (!(ok[v] & x)) self(self, v, tmp, x);
    };
    dfs(dfs, id_mp[0], adj, 1);
    dfs(dfs, id_mp[0], inv_adj, 2);
    bool ret = false;
    FOR (i, n) if (!(ok[i] & 2)) cout << "TRAPPED " << ids[i] << '\n', ret = true;
    FOR (i, n) if (!(ok[i] & 1)) cout << "UNREACHABLE " << ids[i] << '\n', ret = true;
    if (!ret) cout << "NO PROBLEMS\n";

    return 0;
}