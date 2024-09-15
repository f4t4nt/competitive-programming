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
    pld,
    null_type,
    less<pld>,
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
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
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

    // vector<bool> used(10);
    // set<pll> edges;
    // while (sz(edges) < 50 || used != vector<bool>(10, 1)) {
    //     ll u = rng() % 10, v = rng() % 10;
    //     while (u == v || edges.count({u, v})) {
    //         u = rng() % 10, v = rng() % 10;
    //     }
    //     used[u] = used[v] = 1;
    //     edges.insert({u, v});
    // }

    // cout << 10 << ' ' << sz(edges) << '\n';
    // for (pll e : edges) cout << e.f + 1 << ' ' << e.s + 1 << '\n';

    // return 0;

    ll n, m; cin >> n >> m;
    vector<pll> edges;
    vector<vector<ll>> adj(n);
    FOR (i, m) {
        ll u, v; cin >> u >> v;
        u--, v--;
        edges.pb({u, v});
        adj[u].pb(v);
        adj[v].pb(u);
    }

    FOR (i, n) {
        ssort(adj[i]);
        adj[i].erase(unique(all(adj[i])), adj[i].end());
        if (binary_search(all(adj[i]), i))
        adj[i].erase(find(all(adj[i]), i));
    }

    // FOR (i, n) {
    //     pll best = {-1, -1};
    //     for (ll j : adj[i]) {
    //         ll cnt = 0;
    //         for (ll k : adj[j]) {
    //             if (k == i) continue;
    //             if (binary_search(all(adj[i]), k)) cnt++;
    //         }
    //         if (cnt > best.f) best = {cnt, j};
    //     }
    //     cout << best.s + 1 << ' ';
    // }
    // cout << '\n';

    // return 0;
    
    map<pll, ll> cnt;
    FOR (i, n) {
        ssort(adj[i]);
        FOR (jdx, sz(adj[i])) {
            for (ll kdx = jdx + 1; kdx < sz(adj[i]); kdx++) {
                ll j = adj[i][jdx], k = adj[i][kdx];
                cnt[{j, k}]++;
                cnt[{k, j}]++;
            }
        }
    }

    FOR (i, n) {
        pll best = {-1, -1};
        for (ll j : adj[i]) {
            pll cur = {i, j};
            if (cnt[cur] > best.f) best = {cnt[cur], j};
        }
        cout << best.s + 1 << ' ';
    }
    cout << '\n';

    return 0;
}