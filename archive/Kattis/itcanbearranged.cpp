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

const ll INF = 1e9;

struct Edge {
    ll s, t, cap = 0, flow = 0;
};

struct Dinic {
    ll n;
    vector<Edge> edges;
    vector<vector<ll>> adj;
    vector<ll> lvl, ptr;
    queue<ll> q;

    Dinic(ll n, vector<Edge> &edges0) :
        n(n), adj(n), lvl(n), ptr(n) {
        ll i = 0;
        FORE (e, edges0) {
            edges.pb(e);
            edges.pb({e.t, e.s});
            adj[e.s].pb(i++);
            adj[e.t].pb(i++);
        }
    }

    bool bfs(ll s, ll t) {
        lvl.assign(n, -1);
        lvl[s] = 0;
        q.push(s);
        while (!q.empty()) {
            ll v = q.front();
            q.pop();
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
            ll e = adj[v][cid];
            ll u = edges[e].t;
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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll T; cin >> T;
    FOR (t, T) {
        ll n, m; cin >> n >> m;
        vector<ll> t_lo(n), t_hi(n), cnt(n);
        FOR (i, n) cin >> t_lo[i] >> t_hi[i] >> cnt[i], cnt[i] = (cnt[i] + m - 1) / m;
        vector<vector<ll>> t_clean(n, vector<ll>(n));
        FOR (i, n) FOR (j, n) cin >> t_clean[i][j];
        vector<vector<bool>> adj(n, vector<bool>(n));
        FOR (i, n) FOR (j, n) adj[i][j] = t_hi[i] + t_clean[i][j] < t_lo[j];
        ll snk = 0, src = 1, node_lo = 2, node_hi = 3;
        vector<Edge> edges;
        edges.pb({node_lo, node_hi, INF});
        FOR (i, n) {
            ll i_lo = 4 + i, i_hi = 4 + n + i;
            edges.pb({src, i_lo, cnt[i]});
            edges.pb({i_lo, node_lo, INF});
            edges.pb({node_hi, i_hi, INF});
            edges.pb({i_hi, snk, cnt[i]});
            FOR (j, n) {
                ll j_hi = 4 + n + j;
                if (adj[i][j]) edges.pb({i_lo, j_hi, INF});
            }
        }
        ll mx = accumulate(all(cnt), 0LL),
            lo = 1, hi = mx;
        while (lo < hi) {
            ll mid = (lo + hi) / 2;
            edges[0].cap = mid;
            Dinic dinic(2 * n + 4, edges);
            ll flow = dinic.max_flow(src, snk);
            if (flow == mx) hi = mid;
            else lo = mid + 1;
        }
        cout << "Case " << t + 1 << ": " << lo << '\n';
    }

    return 0;
}