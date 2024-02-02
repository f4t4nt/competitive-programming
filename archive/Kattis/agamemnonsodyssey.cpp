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

ll dfs(ll u, ll p, ll &rv, vector<vector<pair<ll, ll>>> &adj) { // ??
    multiset<ll> best;
    for (auto [v, c] : adj[u]) {
        if (v == p) continue;
        ll mx = dfs(v, u, rv, adj);
        best.insert(mx + c);
    }
    ll nv = 0, mx = 0;
    if (sz(best) > 0) {
        mx = *best.rbegin();
        nv = *best.rbegin();
        if (sz(best) > 1) nv += *next(best.rbegin());
    }
    rv = max(rv, nv);
    return mx;
}

pair<ll, ll> max_dist(ll u, vector<vector<pair<ll, ll>>> &adj) {
    vector<ll> dist(sz(adj), 0);
    std::priority_queue<pair<ll, ll>> pq;
    pq.push({0, u});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (dist[v] != 0) continue;
        dist[v] = -d;
        for (auto [w, c] : adj[v]) {
            if (dist[w] != 0) continue;
            if (w == u) continue;
            pq.push({d - c, w});
        }
    }
    ll mx = 0, v = 0;
    FOR (i, sz(adj)) {
        if (dist[i] > mx) {
            mx = dist[i];
            v = i;
        }
    }
    return {mx, v};
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k, rv = 0; cin >> n >> k;
    vector<vector<pair<ll, ll>>> adj(n);
    FOR (i, n - 1) {
        ll u, v, c; cin >> u >> v >> c; 
        u--; v--;
        rv += c;
        adj[u].pb({v, c});
        adj[v].pb({u, c});
    }
    if (k == 1) {
        rv = 0;
        // auto [d, u] = max_dist(0, adj);
        // auto [d2, v] = max_dist(u, adj);
        // rv = d2;
        dfs(0, -1, rv, adj);
    }
    cout << rv << '\n';

    return 0;
}