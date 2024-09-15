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
// #define f first
// #define s second

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

const ll MOD = 998244353;

ll poww(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

map<ll, ll> inv_mem;

ll inv(ll a) {
    if (inv_mem.count(a)) return inv_mem[a];
    return inv_mem[a] = poww(a, MOD - 2);
}

ll frac(ll a, ll b) {
    return a * inv(b) % MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> parent(n, -1), root(n, -1), dist_up(n, -1), dist_down(n, -1);
        vector<vector<ll>> adj(n), children(n);
        FOR (i, n - 1) {
            ll u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        auto dfs = [&](auto &&f, ll v, ll p) -> void {
            parent[v] = p;
            for (ll u : adj[v]) {
                if (u == p) continue;
                children[v].pb(u);
                f(f, u, v);
            }
        };
        dfs(dfs, 0, -1);
        queue<ll> bfs;
        FOR (i, n) if (sz(children[i]) == 0) bfs.push(i), dist_down[i] = 0;
        while (!bfs.empty()) {
            ll v = bfs.front(); bfs.pop();
            ll u = parent[v];
            if (dist_down[u] != -1) continue;
            dist_down[u] = dist_down[v] + 1;
            bfs.push(u);
        }
        vector<ll> in_ord = {0};
        bfs.push(0), dist_up[0] = 0, root[0] = 0;
        while (!bfs.empty()) {
            ll v = bfs.front(); bfs.pop();
            for (ll u : children[v]) {
                if (dist_down[u] == dist_down[v] - 1) {
                    dist_up[u] = dist_up[v] + 1;
                    root[u] = root[v];
                } else {
                    dist_up[u] = 1;
                    root[u] = v;
                }
                bfs.push(u);
                in_ord.pb(u);
            }
        }
        vector<ll> res(n, -1);
        res[0] = 1;
        FOR (i, n) {
            if (i == 0) continue;
            ll v = in_ord[i];
            ll d_up = dist_up[v], d_down = dist_down[v], d = d_up + d_down;
            ll rt = root[v];
            res[v] = (res[rt] * frac(d_down, d)) % MOD;
        }
        FOR (i, n) cout << res[i] << ' ';
        cout << '\n';
    }

    return 0;
}