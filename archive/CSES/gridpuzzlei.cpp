#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
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

struct Edge {
    ll s, t, cap = 0, cost = 0, flow = 0;
};

struct Dinic { // matrix
    ll n;
    vector<Edge> edges;
    vector<vector<ll>> adj, caps, flows, costs;
    vector<ll> lvl, ptr;
    queue<ll> q;

    Dinic(ll n, vector<Edge> &edges) :
        n(n), adj(n), edges(edges),
        caps(n, vector<ll>(n)),
        flows(n, vector<ll>(n)),
        costs(n, vector<ll>(n))
    {
        FORE (e, edges) {
            adj[e.s].pb(e.t);
            adj[e.t].pb(e.s);
            caps[e.s][e.t] = e.cap;
            costs[e.s][e.t] = e.cost;
        }
    }

    bool bfs(ll s, ll t) {
        lvl.assign(n, -1);
        lvl[s] = 0;
        q.push(s);
        while (!q.empty()) {
            ll v = q.front();
            q.pop();
            FORE (u, adj[v]) {
                if (lvl[u] != -1 || caps[v][u] <= flows[v][u]) {
                    continue;
                }
                lvl[u] = lvl[v] + 1;
                q.push(u);
            }
        }
        return lvl[t] != -1;
    }

    ll dfs(ll v, ll t, ll f) {
        if (v == t || f == 0) {
            return f;
        }
        for (ll &cid = ptr[v]; cid < sz(adj[v]); cid++) {
            ll u = adj[v][cid];
            if (lvl[v] + 1 != lvl[u] || caps[v][u] <= flows[v][u]) {
                continue;
            }
            ll tr = dfs(u, t, min(f, caps[v][u] - flows[v][u]));
            if (tr == 0) {
                continue;
            }
            flows[v][u] += tr;
            flows[u][v] -= tr;
            return tr;
        }
        return 0;
    }

    ll max_flow(ll s, ll t) {
        ll flow = 0;
        while (true) {
            if (!bfs(s, t)) {
                break;
            }
            ptr.assign(n, 0);
            while (ll pushed = dfs(s, t, LLONG_MAX)) {
                flow += pushed;
            }
        }
        return flow;
    }

    vector<pair<ll, ll>> min_cut(ll s) {
        bfs(s, -1);
        vector<pair<ll, ll>> cut;
        FORE (e, edges) {
            if (lvl[e.s] != -1 && lvl[e.t] == -1 && caps[e.s][e.t] > 0) {
                cut.pb({e.s, e.t});
            }
        }
        return cut;
    }

    void undo_flow(vector<ll> path, ll f) {
        FOB (i, 1, sz(path)) {
            flows[path[i - 1]][path[i]] -= f;
            flows[path[i]][path[i - 1]] += f;
            assert(flows[path[i - 1]][path[i]] >= 0);
            assert(flows[path[i]][path[i - 1]] >= 0);
            assert(flows[path[i - 1]][path[i]] <= caps[path[i - 1]][path[i]]);
            assert(flows[path[i]][path[i - 1]] <= caps[path[i]][path[i - 1]]);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, a_sum, b_sum;
    cin >> n;
    vector<ll> a(n), b(n);
    FORE (ai, a) {
        cin >> ai;
    }
    FORE (bi, b) {
        cin >> bi;
    }
    a_sum = accumulate(all(a), 0LL);
    b_sum = accumulate(all(b), 0LL);
    if (a_sum != b_sum) {
        cout << -1 << '\n';
        return 0;
    }
    ll src = 2 * n, snk = 2 * n + 1;
    vector<Edge> edges;
    FOR (i, n) {
        edges.pb({src, i, a[i]});
        edges.pb({i + n, snk, b[i]});
    }
    FOR (i, n) {
        FOR (j, n) {
            edges.pb({i, j + n, 1});
        }
    }
    Dinic dinic(2 * n + 2, edges);
    ll flow = dinic.max_flow(src, snk);
    if (flow != a_sum) {
        cout << -1 << '\n';
        return 0;
    }
    vector<str> rv(n, str(n, '.'));
    FOR (i, n) {
        FORE (u, dinic.adj[i]) {
            if (u == src || u == snk) {
                continue;
            }
            if (dinic.flows[i][u] == 1) {
                rv[i][u - n] = 'X';
            }
        }
    }
    FORE (r, rv) {
        cout << r << '\n';
    }

    return 0;
}