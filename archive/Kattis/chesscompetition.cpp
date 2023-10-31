#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
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

const ll INF = 1e18;

struct Edge {
    ll s, t, cap = 0, cost = 0, flow = 0;
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
            while (ll pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }

    vector<pair<ll, ll>> min_cut(ll s) {
        bfs(s, n - 1);
        vector<pair<ll, ll>> cut;
        FORE (e,edges) {
            if (lvl[e.s] != -1 && lvl[e.t] == -1 && e.cap > 0) {
                cut.pb({e.s, e.t});
            }
        }
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

bool ok(ll &i0, ll &n, vector<str> &past) {
    vector<ll> cur(n), rem(n);
    vector<pair<ll, ll>> unplayed;
    FOR (i, n) {
        FOR (j, n) {
            if (past[i][j] == '1') {
                cur[i] += 2;
            } elif (past[i][j] == 'd') {
                cur[i] += 1;
            } elif (past[i][j] == '.' && i < j) {
                unplayed.pb({i, j});
            }
        }
    }
    FOR (i, n) {
        if (cur[i0] < cur[i]) {
            return false;
        }
        rem[i] = cur[i0] - cur[i];
    }
    ll m = sz(unplayed);
    vector<Edge> edges;
    ll src = n + m, snk = src + 1;
    FOR (i, m) {
        edges.pb({src, i + n, 2});
        edges.pb({i + n, unplayed[i].first, 2});
        edges.pb({i + n, unplayed[i].second, 2});
    }
    FOR (i, n) {
        edges.pb({i, snk, rem[i]});
    }
    Dinic dinic(snk + 1, edges);
    ll flow = dinic.max_flow(src, snk);
    return flow == 2 * m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<str> past0(n);
        FOR (i, n) {
            cin >> past0[i];
        }
        vector<ll> rv;
        FOR (i, n) {
            auto past = past0;
            FOR (j, n) {
                if (past[i][j] == '.') {
                    past[i][j] = '1';
                    past[j][i] = '0';
                }
            }
            if (ok(i, n, past)) {
                rv.pb(i);
            }
        }
        FORE (x, rv) {
            cout << x + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}