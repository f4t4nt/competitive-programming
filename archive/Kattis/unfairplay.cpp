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

    vector<pll> min_cut(ll s) {
        bfs(s, n - 1);
        vector<pll> cut;
        FORE (e,edges) if (lvl[e.s] != -1 && lvl[e.t] == -1 && e.cap > 0)
            cut.pb({e.s, e.t});
        return cut;
    }

    void undo_flow(vector<ll> path, ll f) {
        FOR (i, sz(path) - 1) {
            FORE (e, adj[path[i]]) {
                if (edges[e].t == path[i + 1]) {
                    edges[e].flow -= f;
                    edges[e ^ 1].flow += f;
                    assert(edges[e].flow <= edges[e].cap);
                    assert(edges[e ^ 1].flow <= edges[e ^ 1].cap);
                    break;
                }
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    while (true) {
        ll n, m; cin >> n;
        if (n == -1) break;
        cin >> m;
        vector<ll> scores(n), ans(m, -1);
        FOR (i, n) cin >> scores[i];
        auto tmp = scores;
        vector<pll> matches(m);
        FOR (i, m) {
            cin >> matches[i].f >> matches[i].s;
            if (matches[i].f == n) {
                scores.back() += 2;
                ans[i] = 0;
            } elif (matches[i].s == n) {
                scores.back() += 2;
                ans[i] = 2;
            }
            matches[i].f--, matches[i].s--;
        }
        bool ok = true;
        FOR (i, n) {
            scores[i] = scores.back() - scores[i];
            if (i != n - 1) scores[i]--;
            if (scores[i] < 0) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            cout << "NO\n";
            continue;
        }
        vector<Edge> edges;
        ll src = n + m, snk = n + m + 1, target = 0;
        FOR (i, m) {
            if (ans[i] == -1) {
                edges.pb({src, n + i, 2});
                edges.pb({n + i, matches[i].f, 2});
                edges.pb({n + i, matches[i].s, 2});
                target += 2;
            } else {
                edges.pb({src, n + i, 0});
                edges.pb({n + i, matches[i].f, 0});
                edges.pb({n + i, matches[i].s, 0});
            }
        }
        FOR (i, n) edges.pb({i, snk, scores[i]});
        Dinic dinic(n + m + 2, edges);
        ll flow = dinic.max_flow(src, snk);
        if (flow == target) {
            FOR (i, m) if (ans[i] == -1) ans[i] = dinic.edges[6 * i + 4].flow;
            FOR (i, m) {
                cout << ans[i] << ' ';
                tmp[matches[i].f] += 2 - ans[i];
                tmp[matches[i].s] += ans[i];
            }
            cout << '\n';
        } else cout << "NO\n";
    }

    return 0;
}