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

#define f first
#define s second

pll dfs0(ll u, ll p, ll d,
    vector<vector<pll>> &adj,
    vector<ll> &tax,
    vector<ll> &dist,
    vector<ll> &subtree_cnt,
    vector<ll> &subtree_tax)
{
    dist[u] = d;
    FORE (v, adj[u]) {
        if (v.f == p) continue;
        auto tmp = dfs0(v.f, u, d + v.s, adj, tax, dist, subtree_cnt, subtree_tax);
        subtree_cnt[u] += tmp.f;
        subtree_tax[u] += tmp.s;
    }
    return {subtree_cnt[u], subtree_tax[u]};
}

void dfs1(ll u, ll p, ll n, ll tot,
    vector<vector<pll>> &adj,
    vector<ll> &subtree_cnt,
    vector<ll> &subtree_tax,
    vector<pll> &rv)
{
    FORE (v, adj[u]) {
        if (v.f == p) continue;
        rv[v.f].f = rv[u].f - subtree_cnt[v.f] * v.s + (n - subtree_cnt[v.f]) * v.s;
        rv[v.f].s = rv[u].s - subtree_tax[v.f] * v.s + (tot - subtree_tax[v.f]) * v.s;
        dfs1(v.f, u, n, tot, adj, subtree_cnt, subtree_tax, rv);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    vector<ll> tax(n), dist(n), subtree_cnt(n, 1), subtree_tax;
    FOR (i, n) cin >> tax[i];
    ll tot = accumulate(all(tax), 0LL);
    subtree_tax = tax;
    vector<vector<pll>> adj(n);
    FOR (i, n - 1) {
        ll u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    // sum dist, sum tax * dist
    vector<pll> rv(n);
    dfs0(0, -1, 0, adj, tax, dist, subtree_cnt, subtree_tax);
    FOR (i, n) {
        rv[0].f += dist[i];
        rv[0].s += tax[i] * dist[i];
    }
    dfs1(0, -1, n, tot, adj, subtree_cnt, subtree_tax, rv);
    FOR (i, n) cout << rv[i].f * tax[i] + rv[i].s << '\n';

    return 0;
}