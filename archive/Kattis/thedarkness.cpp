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
// #define f first
// #define s second

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

const ll INF = 1e9,
    dx[] = {1, -1, 0, 0},
    dy[] = {0, 0, 1, -1};

struct Edge { ll s, t, cap = 0, cost = 0, flow = 0; };

struct Dinic {
    ll n; vector<Edge> edges;
    vector<vector<ll>> adj;
    vector<ll> lvl, ptr;
    queue<ll> q;

    Dinic(ll n, vector<Edge> &edges0) :
        n(n), adj(n), lvl(n), ptr(n) {
        // FORE (e, edges0) {
        for (auto &e : edges0) {
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
            // FORE (e, adj[v]) {
            for (auto &e : adj[v]) {
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
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll b, h, r, c;
    cin >> b >> h >> r >> c;
    vector<str> grid(r), ok(r, str(c, '.'));
    for (str &row : grid) cin >> row;
    vector<vector<ld>> yagami(r, vector<ld>(c));
    FOR (sx, r) FOR (sy, c) {
        ld src = grid[sx][sy] - '0';
        if (src == 0) continue;
        queue<pll> q;
        q.push({sx, sy});
        vector<bitset<31>> vis(31);
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            if (x < 0 || x >= r || y < 0 || y >= c) continue;
            if (vis[x][y]) continue;
            vis[x][y] = 1;
            ll xx = x - sx, yy = y - sy;
            yagami[x][y] += src / (xx * xx + yy * yy + h * h);
            FOR (k, 4) {
                ll nx = x + dx[k], ny = y + dy[k];
                if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
                q.push({nx, ny});
            }
        }
    }
    FOR (i, r) FOR (j, c) if (yagami[i][j] >= b) ok[i][j] = '*';
    // for (str &row : ok) cerr << row << '\n';
    vector<Edge> edges;
    ll SRC = r * c, SNK = SRC + 1;
    FOR (i, r) FOR (j, c) if (ok[i][j] == '.')
        edges.pb({i * c + j, SNK, INF});
    FOR (i, r) FOR (j, c) {
        ll cap = (i == 0) + (i == r - 1) + (j == 0) + (j == c - 1);
        if (cap > 0) {
            edges.pb({SRC, i * c + j, INF});
        }
        FOR (k, 4) {
            ll ni = i + dx[k], nj = j + dy[k];
            if (ni < 0 || ni >= r || nj < 0 || nj >= c)
                continue;
            if (ok[i][j] == '*' && ok[ni][nj] == '*') 
                edges.pb({i * c + j, ni * c + nj, 43});
            else
                edges.pb({i * c + j, ni * c + nj, 11});
        }
    }
    Dinic dinic(r * c + 2, edges);
    ll res = dinic.max_flow(SRC, SNK);
    cout << res << '\n';

    return 0;
}