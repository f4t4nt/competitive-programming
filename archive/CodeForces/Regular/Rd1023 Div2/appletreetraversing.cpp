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

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
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

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

vector<ll> dist, par, touched;

ll bfs(ll src, vector<vector<ll>> &adj, vector<bool> &used) {
    touched = {src};
    queue<ll> q;
    q.push(src);
    dist[src] = 0;
    par[src]  = -1;

    ll dst = src;
    while (!q.empty()) {
        ll v = q.front(); q.pop();
        if (dist[v] > dist[dst] ||(dist[v] == dist[dst] && v > dst))
            dst = v;
        for (ll u: adj[v]) {
            if (!used[u] && dist[u] == -1) {
                dist[u] = dist[v] + 1;
                par[u]  = v;
                q.push(u);
                touched.pb(u);
            }
        }
    }

    for (ll v: touched) dist[v] = -1;
    return dst;
}

tuple<ll, ll, ll, ll> build(
    ll start,
    vector<vector<ll>> &adj,
    vector<bool> &used,
    vector<bool> &vis,
    vector<vector<ll>> &paths)
{
    ll src = bfs(start, adj, used);
    for (ll v: touched) vis[v] = true;

    ll dst = bfs(src, adj, used);
    vector<ll> path;
    for (ll v = dst; v != -1; v = par[v]) {
        path.pb(v);
        if (v == src) break;
    }

    paths.pb(path);
    return {sz(path), max(src, dst), min(src, dst), sz(paths) - 1};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t;  cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<vector<ll>> adj(n);
        for (ll i = 1; i < n; i++) {
            ll u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }

        dist = vector<ll>(n, -1), par = dist;
        touched.clear();

        std::priority_queue<tuple<ll, ll, ll, ll>> pq;
        vector<vector<ll>> paths;
        vector<ll> ans;
        vector<bool> vis(n), used(n);

        pq.push(build(0, adj, used, vis, paths));
        vis = vector<bool>(n);
        while (!pq.empty()) {
            auto [len, u, v, pid] = pq.top(); pq.pop();
            ans.pb(len);
            ans.pb(u + 1);
            ans.pb(v + 1);

            for (ll x : paths[pid]) used[x] = true;
            for (ll x : paths[pid]) {
                for (ll u : adj[x]) {
                    if (!used[u] && !vis[u]) {
                        pq.push(build(u, adj, used, vis, paths));
                    }
                }
            }

            vis = vector<bool>(n);
        }

        for (ll x : ans) cout << x << ' ';
        cout << '\n';
    }

    return 0;
}
