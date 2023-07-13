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

constexpr ll INF = 1e18;

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

    void unpack(vector<tuple<ll, ll, ll>> &rv, vector<ll> &cnts, ll &m) {
        FOR (u, m) {
            ll a = -1, b, c;
            FOR (j, sz(adj[u])) {
                ll v = adj[u][j];
                if (caps[u][v] > 0) {
                    assert(caps[u][v] == 2);
                    if (a == -1) {
                        a = v - m;
                        c = flows[u][v];
                        cnts[a] -= c;
                    } else {
                        b = v - m;
                        cnts[b] -= flows[u][v];
                    }
                }
            }
            rv.pb({a, b, c});
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<ll> cnts(n);
    FOR (i, n) {
        cin >> cnts[i];
    }
    vector<pair<ll, ll>> purchases(m);
    FOR (i, m) {
        cin >> purchases[i].first >> purchases[i].second;
        purchases[i].first--, purchases[i].second--;
    }
    ll s = n + m, t = s + 1;
    vector<Edge> edges;
    FOR (i, m) {
        edges.pb({s, i, 2});
        edges.pb({i, m + purchases[i].first, 2});
        edges.pb({i, m + purchases[i].second, 2});
    }
    FOR (i, n) {
        edges.pb({m + i, t, cnts[i]});
    }
    Dinic dinic(n + m + 2, edges);
    ll flow = dinic.max_flow(s, t);
    vector<tuple<ll, ll, ll>> rv;
    dinic.unpack(rv, cnts, m);
    vector<ll> evens(n);
    queue<ll> q;
    FOR (i, n) {
        evens[i] = cnts[i] / 2;
        if (cnts[i] % 2 == 1) {
            q.push(i);
        }
    }
    FOR (i, evens[0]) {
        rv.pb({0, 1, 2});
    }
    FOB (i, 1, n) {
        FOR (j, evens[i]) {
            rv.pb({i, 0, 2});
        }
    }
    assert(sz(q) % 2 == 0);
    while (!q.empty()) {
        ll a = q.front();
        q.pop();
        ll b = q.front();
        q.pop();
        rv.pb({a, b, 1});
    }
    cout << sz(rv) << '\n';
    FORE (t, rv) {
        cout << get<0>(t) + 1 << ' ' << get<1>(t) + 1 << ' ' << get<2>(t) << '\n';
    }

    return 0;
}