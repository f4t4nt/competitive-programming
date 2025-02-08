#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
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
#define x first
#define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

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
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    vector<ll> times(n), total(n), subsz(n);
    vector<vector<ll>> adj(n);
    FOR (i, n) {
        cin >> times[i];
        ll k; cin >> k;
        adj[i].resize(k);
        FOR (j, k) {
            cin >> adj[i][j];
            adj[i][j]--;
        }
    }

    auto dfs = [&](auto &&self, ll u) -> pll {
        total[u] = times[u];
        subsz[u] = 1;
        for (ll v : adj[u]) {
            auto [t, s] = self(self, v);
            total[u] += t;
            subsz[u] += s;
        }
        return {total[u], subsz[u]};
    };
    dfs(dfs, 0);

    ll ans = 0, cur_u = 0, cur_t = 0;
    auto dfs2 = [&](auto &&self, ll u) -> void {
        vector<pair<ld, ll>> sorted_adj;
        for (ll v : adj[u]) sorted_adj.pb({(ld) total[v] / subsz[v], v});
        ssort(sorted_adj);
        cur_t++;
        for (auto [_, v] : sorted_adj) {
            self(self, v);
        }
        cur_t += times[u];
        ans += cur_t;
    };
    dfs2(dfs2, 0);

    cout << ans << '\n';

    return 0;
}