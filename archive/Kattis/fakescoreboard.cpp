#include <bits/stdc++.h>

using namespace std;

using ll = long long;
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

struct Edge {
    ll s, t, cap, cost;
};

struct Dinic { 
    ll n, flow = 0;
    vector<vector<ll>> adj, caps, flows;
    vector<ll> lvl, ptr;
    queue<ll> q;

    Dinic(ll n, vector<Edge> &edges) :
        n(n), adj(n),
        caps(n, vector<ll>(n)),
        flows(n, vector<ll>(n)),
        lvl(n), ptr(n)
    {
        FORE (e, edges) {
            adj[e.s].pb(e.t);
            adj[e.t].pb(e.s);
            caps[e.s][e.t] = e.cap;
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
        flow = 0;
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
};

vector<vector<ll>> dinic_to_sums(ll t, ll p, Dinic dinic) {
    vector<vector<ll>> rv = {vector<ll>(t), vector<ll>(p)};
    FOR (i, t) {
        FORE (j, dinic.adj[i]) {
            if (dinic.flows[i][j] == 1) {
                rv[0][i]++;
                rv[1][j - t]++;
            }
        }
    }
    return rv;
}

vector<str> dinic_to_str(ll t, ll p, vector<str> ans, Dinic dinic) {
    vector<str> rv(t, str(p, 'N'));
    FOR (i, t) {
        FORE (j, dinic.adj[i]) {
            if (dinic.flows[i][j] == 1 || ans[i][j - t] == 'Y') {
                rv[i][j - t] = 'Y';
            }
        }
    }
    return rv;
}

vector<vector<ll>> vec_to_sums(ll t, ll p, vector<str> ans) {
    vector<vector<ll>> rv = {vector<ll>(t), vector<ll>(p)};
    FOR (i, t) {
        FOR (j, p) {
            if (ans[i][j] == 'Y') {
                rv[0][i]++;
                rv[1][j]++;
            }
        }
    }
    return rv;
}

bool vec_vec_equal(vector<vector<ll>> a, vector<vector<ll>> b) {
    if (sz(a) != sz(b)) {
        return false;
    }
    FOR (i, sz(a)) {
        if (sz(a[i]) != sz(b[i])) {
            return false;
        }
        FOR (j, sz(a[i])) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ll t, p, totalt = 0, totalp = 0;
        cin >> t >> p;
        if (t == 0 && p == 0) break;
        vector<ll> teams(t), problems(p);
        FOR (i, t) {
            cin >> teams[i];
            totalt += teams[i];
        }
        FOR (i, p) {
            cin >> problems[i];
            totalp += problems[i];
        }
        if (totalt != totalp) {
            cout << "Impossible\n";
            continue;
        }
        vector<Edge> edges;
        ll src = t + p, sink = src + 1;
        FOR (i, t) {
            edges.pb({src, i, teams[i]});
        }
        FOR (i, t) {
            FOR (j, p) {
                edges.pb({i, t + j, 1, 1});
            }
        }
        FOR (i, p) {
            edges.pb({t + i, sink, problems[i]});
        }
        Dinic dinic(sink + 1, edges);
        ll flow = dinic.max_flow(src, sink);
        if (flow != totalt) {
            cout << "Impossible\n";
            continue;
        }
        vector<str> rv(t, str(p, 'N'));
        FOR (i, t) {
            FORE (j, dinic.adj[i]) {
                if (j < t || j >= t + p) continue;
                dinic.caps[i][j] = 0;
                if (dinic.flows[i][j] == 1) {
                    dinic.flows[src][i]--;
                    dinic.flows[i][src]++;
                    dinic.flows[i][j]--;
                    dinic.flows[j][i]++;
                    dinic.flows[j][sink]--;
                    dinic.flows[sink][j]++;
                    auto dinic0 = dinic;
                    ll tmp = dinic.max_flow(src, sink);
                    if (tmp == 0) {
                        rv[i][j - t] = 'Y';
                        totalt--;
                        dinic = dinic0;
                        dinic.caps[src][i]--;
                        dinic.caps[j][sink]--;
                    }
                }
            }
        }
        FOR (i, t) {
            FOR (j, p) {
                cout << rv[i][j];
            }
            cout << '\n';
        }
    }

    return 0;
}