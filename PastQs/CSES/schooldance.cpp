#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define ins insert
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

struct Dinic {
    struct Edge {
        ll from, to, cap, flow = 0;
        Edge(ll from, ll to, ll cap) : from(from), to(to), cap(cap) {}
    };

    ll n, m = 0;
    vector<Edge> edges;
    vector<vector<ll>> adj;
    vector<ll> level, ptr;
    queue<ll> q;

    Dinic(ll n) : n(n) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    Dinic(vector<vector<pair<ll, ll>>> adj) {
        n = sz(adj);
        this->adj.resize(n);
        level.resize(n);
        ptr.resize(n);
        FOR (i, n) {
            FORE (e, adj[i]) {
                add_edge(i, e.first, e.second);
            }
        }
    }

    void add_edge(ll from, ll to, ll cap) {
        edges.pb({from, to, cap});
        edges.pb({to, from, 0});
        adj[from].pb(m);
        adj[to].pb(m + 1);
        m += 2;
    }

    bool bfs(ll s, ll t) {
        while (!q.empty()) {
            ll v = q.front();
            q.pop();
            for (ll id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1) {
                    continue;
                }
                if (level[edges[id].to] != -1) {
                    continue;
                }
                level[edges[id].to] = level[v] + 1;
                q.push(edges[id].to);
            }
        }
        return level[t] != -1;
    }

    ll dfs(ll v, ll t, ll pushed) {
        if (pushed == 0) {
            return 0;
        }
        if (v == t) {
            return pushed;
        }
        for (ll &cid = ptr[v]; cid < (ll) adj[v].size(); cid++) {
            ll id = adj[v][cid];
            ll u = edges[id].to;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) {
                continue;
            }
            ll tr = dfs(u, t, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0) {
                continue;
            }
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    ll max_flow(ll s, ll t) {
        ll flow = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs(s, t)) {
                break;
            }
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(s, t, LLONG_MAX)) {
                flow += pushed;
            }
        }
        return flow;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, k;
    cin >> n >> m >> k;
    ll source = n + m, sink = n + m + 1;
    vector<vector<pair<ll, ll>>> adj(sink + 1);
    FOR (i, k) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb({n + b, 1});
        adj[n + b].pb({a, 0});
    }
    FOR (i, n) {
        adj[source].pb({i, 1});
        adj[i].pb({source, 0});
    }
    FOR (i, m) {
        adj[n + i].pb({sink, 1});
        adj[sink].pb({n + i, 0});
    }
    Dinic dinic(adj);
    cout << dinic.max_flow(source, sink) << '\n';
    vector<pair<ll, ll>> matching;
    FOR (i, n) {
        FORE (id, dinic.adj[i]) {
            if (dinic.edges[id].flow == 1) {
                matching.pb({i, dinic.edges[id].to - n});
            }
        }
    }
    FORE (e, matching) {
        cout << e.first + 1 << ' ' << e.second + 1 << '\n';
    }

    return 0;
}