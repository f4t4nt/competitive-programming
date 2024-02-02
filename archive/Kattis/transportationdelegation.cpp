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
        while (sz(q)) {
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
            while (ll pushed = dfs(s, t, LLONG_MAX)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll s, r, f, t;
    cin >> s >> r >> f >> t;
    map<str, ll> ids;
    vector<str> states;
    FOR (i, r) {
        str state; cin >> state;
        states.pb(state);
        ids[state] = i;
    }
    FOR (i, f) {
        str state; cin >> state;
        states.pb(state);
        ids[state] = i + r;
    }
    ll src = 2 * s + 2 * t, snk = src + 1;
    vector<Edge> edges;
    FOR (i, r) {
        edges.pb({src, 2 * i, 1});
    }
    FOR (i, f) {
        edges.pb({2 * (i + r) + 1, snk, 1});
    }
    FOR (i, s + t) {
        edges.pb({2 * i, 2 * i + 1, 1});
    }
    FOR (i, t) {
        ll n; cin >> n;
        FOR (j, n) {
            str state; cin >> state;
            if (ids.find(state) == ids.end()) {
                ids[state] = sz(states);
                states.pb(state);
            }
            edges.pb({2 * ids[state] + 1, 2 * s + 2 * i, 1});
            edges.pb({2 * s + 2 * i + 1, 2 * ids[state], 1});
        }
    }
    Dinic dinic(snk + 1, edges);
    cout << dinic.max_flow(src, snk) << '\n';

    return 0;
}