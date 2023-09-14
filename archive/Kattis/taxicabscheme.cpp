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

struct Taxi {
    ll time, x0, y0, x1, y1;
};

ll dist(ll x0, ll y0, ll x1, ll y1) {
    return abs(x0 - x1) + abs(y0 - y1);
}

// can we take taxi a and then taxi b?
bool is_adj(Taxi a, Taxi b) {
    return a.time + dist(a.x1, a.y1, a.x0, a.y0) + dist(a.x1, a.y1, b.x0, b.y0) < b.time;
}

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
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<Taxi> taxis(n);
        FOR (i, n) {
            str time;
            ll hh, mm, x0, y0, x1, y1;
            cin >> time >> x0 >> y0 >> x1 >> y1;
            hh = (time[0] - '0') * 10 + (time[1] - '0');
            mm = (time[3] - '0') * 10 + (time[4] - '0');
            taxis[i] = {hh * 60 + mm, x0, y0, x1, y1};
        }
        vector<Edge> edges;
        ll src = 2 * n, sink = src + 1;
        // minimum matching, edge from i to j + n iff is_adj(i, j)
        FOR (i, n) {
            FOB (j, 1, n) {
                if (i != j && is_adj(taxis[i], taxis[j])) {
                    edges.pb({i, j + n, 1});
                }
            }
        }
        // edges from src to i and from i + n to sink
        FOR (i, n) {
            edges.pb({src, i, 1});
            edges.pb({i + n, sink, 1});
        }
        Dinic matching(sink + 1, edges);
        matching.max_flow(src, sink);
        ll rv = n;
        vector<bool> matched(n);
        FORE (e, matching.edges) {
            if (e.s < n && e.t >= n && e.flow == 1 && !matched[e.s]) {
                rv--;
                matched[e.s] = true;
            }
        }
        cout << rv << '\n';
    }

    return 0;
}