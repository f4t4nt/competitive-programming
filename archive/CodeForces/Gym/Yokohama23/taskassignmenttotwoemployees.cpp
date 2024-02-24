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

const ll INF = 1e18;

struct Edge { ll s, t, cap = 0, cost = 0, flow = 0; };

struct Dinic {
    ll n; vector<Edge> edges;
    vector<vector<ll>> adj;
    vector<ll> lvl, ptr;
    queue<ll> q;

    Dinic(ll n, vector<Edge> &edges0) :
        n(n), adj(n), lvl(n), ptr(n) {
        FORE (e, edges0) {
            adj[e.s].pb(sz(edges));
            edges.pb(e);
            adj[e.t].pb(sz(edges));
            edges.pb({e.t, e.s});
        }
    }

    bool bfs(ll s, ll t) {
        lvl.assign(n, -1); lvl[s] = 0; q.push(s);
        while (!q.empty()) {
            ll v = q.front(); q.pop();
            FORE (e, adj[v]) {
                ll u = edges[e].t;
                if (lvl[u] != -1 || edges[e].cap <= edges[e].flow) continue;
                lvl[u] = lvl[v] + 1;
                q.push(u);
            }
        }
        return lvl[t] != -1;
    }

    ll dfs(ll v, ll t, ll f) {
        if (v == t || f == 0) return f;
        for (ll &cid = ptr[v]; cid < sz(adj[v]); cid++) {
            ll e = adj[v][cid], u = edges[e].t;
            if (lvl[v] + 1 != lvl[u]) continue;
            ll pushed = dfs(u, t, min(f, edges[e].cap - edges[e].flow));
            if (pushed) {
                edges[e].flow += pushed;
                edges[e ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    ll max_flow(ll s, ll t) {
        ll flow = 0;
        while (bfs(s, t)) {
            ptr.assign(n, 0);
            while (ll pushed = dfs(s, t, INF)) flow += pushed;
        }
        return flow;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, p0, tot = 0; cin >> n >> p0;
    vector<vector<ll>> s(2, vector<ll>(n)), v = s;
    FOR (i, 2) FOR (j, n) cin >> s[i][j];
    FOR (i, 2) FOR (j, n) cin >> v[i][j];
    vector<Edge> edges;
    ll src = n, snk = n + 1, cnt = n + 2;
    FOR (i, n) {
        tot += p0 * (v[0][i] + v[1][i]);
        edges.pb({src, i, p0 * v[0][i]});
        edges.pb({i, snk, p0 * v[1][i]});
    }
    FOR (i, n) FOB (j, i + 1, n) {
        ll t0 = max(s[0][i] * v[0][j], s[0][j] * v[0][i]),
            t1 = max(s[1][i] * v[1][j], s[1][j] * v[1][i]);
        tot += t0 + t1;
        ll cur = cnt++;
        edges.pb({src, cur, t0});
        edges.pb({cur, i, INF});
        edges.pb({cur, j, INF});
        cur = cnt++;
        edges.pb({cur, snk, t1});
        edges.pb({i, cur, INF});
        edges.pb({j, cur, INF});
    }
    Dinic dinic(cnt, edges);
    ll flow = dinic.max_flow(src, snk);
    cout << tot - flow << '\n';

    return 0;
}