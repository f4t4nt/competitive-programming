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
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
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

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

struct DSU {
    ll cnt; vector<ll> e, edge_cnt;
    DSU(ll n) : cnt(n), e(n, -1), edge_cnt(n) {}
    void reset() { e = vector<ll>(sz(e), -1); cnt = sz(e); }
    ll get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool same_set(ll a, ll b) { return get(a) == get(b); }
    ll size(ll x) { return -e[get(x)]; }
    bool unite(ll x, ll y) {
        x = get(x), y = get(y);
        if (x == y) {
            edge_cnt[x]++;
            return false;
        }
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y]; e[y] = x;
        edge_cnt[x] += edge_cnt[y] + 1;
        cnt--;
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m; cin >> n >> m;
    DSU dsu(n);
    vector<pll> edges;
    vector<ll> deg(n);
    vector<vector<ll>> adj(n);
    FOR (i, m) {
        ll u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v), adj[v].pb(u);
        deg[u]++, deg[v]++;
        edges.pb({u, v});
        dsu.unite(u, v);
    }
    queue<ll> q;
    vector<ll> vis(n);
    FOR (i, n) if (deg[i] == 1) q.push(i);
    set<pll> ans;
    while (sz(q)) {
        ll u = q.front(); q.pop();
        if (vis[u]) continue;
        ll rt = dsu.get(u);
        if (dsu.size(rt) == dsu.edge_cnt[rt] + 1) {
            ll v = adj[u][0];
            vis[u] = -1;
            ans.insert({u, v});
        } else {
            vis[u] = 1;
            FORE (v, adj[u]) {
                if (!vis[v]) {
                    deg[v]--;
                    if (deg[v] == 1) q.push(v);
                } else assert(deg[v] == 1);
            }
        }
    }
    for (auto [u, v] : edges) {
        if (vis[u] == 1 && vis[v] == 0) ans.insert({v, u});
        elif (vis[v] == 1 && vis[u] == 0) ans.insert({u, v});
    }
    cout << sz(ans) << '\n';
    for (auto [u, v] : ans) cout << u + 1 << ' ' << v + 1 << '\n';

    return 0;
}