#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

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

// https://cses.fi/problemset/task/1711

struct Dinic {
    struct Edge {
        ll from, to, cap, flow = 0;
        Edge(ll from, ll to, ll cap) : from(from), to(to), cap(cap) {}
    };

    ll n, m = 0;
    vector<Edge> edges;
    vector<vector<ll>> adj;
    vector<ll> level, ptr;
    vector<vector<ll>> paths;
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

    ll dfs(ll v, ll t, ll pushed, vector<ll> &path) {
        if (pushed == 0) {
            return 0;
        }
        path.pb(v);
        if (v == t) {
            return pushed;
        }
        for (ll &cid = ptr[v]; cid < (ll) adj[v].size(); cid++) {
            ll id = adj[v][cid];
            ll u = edges[id].to;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) {
                continue;
            }
            ll tr = dfs(u, t, min(pushed, edges[id].cap - edges[id].flow), path);
            if (tr == 0) {
                continue;
            }
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        path.pop_back();
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
            vector<ll> path;
            while (ll pushed = dfs(s, t, LLONG_MAX, path)) {
                paths.pb(path);
                flow += pushed;
            }
        }
        return flow;
    }
    
    vector<pair<ll, ll>> min_cut(ll s) {
        bfs(s, -1);
        vector<pair<ll, ll>> cut;
        FOR (i, m) {
            if (level[edges[i].from] != -1 && level[edges[i].to] == -1 && edges[i].cap) {
                cut.pb({edges[i].from, edges[i].to});
            }
        }
        return cut;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<vector<pair<ll, ll>>> adj(n);
    FOR (i, m) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb({b, 1});
    }
    Dinic dinic(adj);

    cout << dinic.max_flow(0, n - 1) << '\n';

    FORE (path, dinic.paths) {
        cout << sz(path) << '\n';
        FORE (v, path) {
            cout << v + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}