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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

// https://open.kattis.com/problems/whowatchesthewatchmen

constexpr ll INF = 1e18;

struct Sentry {
    ld x, y, z, vx, vy, vz, id;
    Sentry(tuple<ll, ll, ll> pos, tuple<ll, ll, ll> dir, ll i) {
        tie(x, y, z) = pos;
        tie(vx, vy, vz) = dir;
        id = i;
    }
    bool operator<(const Sentry &other) const {
        if (x == other.x) {
            if (y == other.y) {
                if (z == other.z) {
                    return id < other.id;
                }
                return z < other.z;
            }
            return y < other.y;
        }
        return x < other.x;
    }
    bool visible(Sentry &other, vector<Sentry> &sentries) {
        if (id == other.id) {
            return false;
        }
        ld dx = other.x - x, dy = other.y - y, dz = other.z - z;
        ld d2 = dx * dx + dy * dy + dz * dz;
        FORE (sentry, sentries) {
            if (sentry.id == id || sentry.id == other.id) {
                continue;
            }
            ld sx = sentry.x - x, sy = sentry.y - y, sz = sentry.z - z;
            if (sx * dy == sy * dx &&
                sx * dz == sz * dx &&
                sy * dz == sz * dy &&
                sx * dx >= 0 &&
                sy * dy >= 0 &&
                sz * dz >= 0)
            {
                ld d2s = sx * sx + sy * sy + sz * sz;
                if (d2s < d2) {
                    return false;
                }
            }
        }
        return true;
    }
    bool sees(Sentry &other, vector<Sentry> &sentries) {
        if (id == other.id) {
            return false;
        }
        ld dx = other.x - x, dy = other.y - y, dz = other.z - z;
        if (dx * vy != dy * vx ||
            dx * vz != dz * vx ||
            dy * vz != dz * vy ||
            dx * vx < 0 ||
            dy * vy < 0 ||
            dz * vz < 0)
        {
            return false;
        }
        return visible(other, sentries);
    }
};

struct Edge {
    ll s, t, cap, cost;
    Edge (ll s, ll t, ll cap, ll cost) : s(s), t(t), cap(cap), cost(cost) {}
};

struct Flow {
    ll n;
    vector<vector<ll>> adj, cap, cap0, cost;

    Flow(ll n, vector<Edge> &edges) : n(n), adj(n), cap(n, vector<ll>(n)), cost(n, vector<ll>(n)) {
        FORE (e, edges) {
            adj[e.s].pb(e.t);
            adj[e.t].pb(e.s);
            cap[e.s][e.t] = e.cap;
            cap[e.t][e.s] = 0;
            cost[e.s][e.t] = e.cost;
        }
        cap0 = cap;
    }

    ll bfs(ll s, ll t, vector<ll> &p) {
        fill(all(p), -1);
        p[s] = -2;
        queue<pair<ll, ll>> q;
        q.push({s, INF});
        while (!q.empty()) {
            ll cur = q.front().first;
            ll flow = q.front().second;
            q.pop();
            FORE (next, adj[cur]) {
                if (p[next] == -1 && cap[cur][next]) {
                    p[next] = cur;
                    ll new_flow = min(flow, cap[cur][next]);
                    if (next == t)
                        return new_flow;
                    q.push({next, new_flow});
                }
            }
        }

        return 0;
    }

    ll max_flow(ll s, ll t) {
        cap = cap0;
        ll flow = 0;
        vector<ll> p(n);
        ll new_flow;
        while (true) {
            new_flow = bfs(s, t, p);
            if (!new_flow) {
                break;
            }
            flow += new_flow;
            ll cur = t;
            while (cur != s) {
                ll prev = p[cur];
                cap[prev][cur] -= new_flow;
                cap[cur][prev] += new_flow;
                cur = prev;
            }
        }
        return flow;
    }

    void dfs(ll u, vector<bool> &vis) {
        vis[u] = true;
        FORE (v, adj[u]) {
            if (!vis[v] && cap[u][v]) {
                dfs(v, vis);
            }
        }
    }

    vector<pair<ll, ll>> min_cut(ll s) {
        vector<bool> vis(n);
        vector<pair<ll, ll>> rv;
        dfs(s, vis);
        FOR (u, n) {
            if (vis[u]) {
                FORE (v, adj[u]) {
                    if (!vis[v]) {
                        rv.pb({u, v});
                    }
                }
            }
        }
        return rv;
    }

    void shortest_paths(ll n, ll v0, vector<ll>& d, vector<ll>& p) {
        d.assign(n, INF);
        d[v0] = 0;
        vector<bool> inq(n, false);
        queue<ll> q;
        q.push(v0);
        p.assign(n, -1);

        while (!q.empty()) {
            ll u = q.front();
            q.pop();
            inq[u] = false;
            FORE (v, adj[u]) {
                if (cap[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                    d[v] = d[u] + cost[u][v];
                    p[v] = u;
                    if (!inq[v]) {
                        inq[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }

    ll min_cost_flow(ll s, ll t, ll k) {
        cap = cap0;
        ll flow = 0;
        ll cost = 0;
        vector<ll> d, p;
        while (flow < k) {
            shortest_paths(n, s, d, p);
            if (d[t] == INF) {
                break;
            }
            ll f = k - flow;
            ll cur = t;
            while (cur != s) {
                f = min(f, cap[p[cur]][cur]);
                cur = p[cur];
            }
            flow += f;
            cost += f * d[t];
            cur = t;
            while (cur != s) {
                cap[p[cur]][cur] -= f;
                cap[cur][p[cur]] += f;
                cur = p[cur];
            }
        }
        if (flow < k) {
            return -1;
        } else {
            return cost;
        }
    }
};

bool all_collinear(vector<Sentry> &sentries) {
    ll n = sz(sentries);
    if (n == 1) {
        return true;
    }
    ld dx0 = sentries[1].x - sentries[0].x,
         dy0 = sentries[1].y - sentries[0].y,
         dz0 = sentries[1].z - sentries[0].z;
    FOR (i, n) {
        ld dx = sentries[i].x - sentries[0].x,
           dy = sentries[i].y - sentries[0].y,
           dz = sentries[i].z - sentries[0].z;
        if (dx * dy0 != dy * dx0 || dx * dz0 != dz * dx0 || dy * dz0 != dz * dy0) {
            return false;
        }
    }
    ssort(sentries);
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<Sentry> sentries;
    FOR (i, n) {
        ll x, y, z, vx, vy, vz;
        cin >> x >> y >> z >> vx >> vy >> vz;
        sentries.pb(Sentry({x, y, z}, {vx, vy, vz}, i));
    }
    // FOR (i, n) {
    //     FOR (j, i) {
    //         assert(sentries[i].x != sentries[j].x || sentries[i].y != sentries[j].y || sentries[i].z != sentries[j].z);
    //     }
    // }
    if (n == 1) {
        cout << -1 << '\n';
        return 0;
    }
    if (n % 2 == 1 && all_collinear(sentries)) {
        
    } else {
        ll s = 2 * n, t = 2 * n + 1;
        vector<Edge> edges;
        vector<vector<ll>> visible(n, vector<ll>(n));
        FOR (i, n) {
            edges.pb(Edge(s, i, 1, 0));
            edges.pb(Edge(i + n, t, 1, 0));
            FOR (j, n) {
                if (sentries[i].sees(sentries[j], sentries)) {
                    edges.pb(Edge(i, j + n, 1, 0));
                    visible[i][j] = 0;
                } elif (sentries[i].visible(sentries[j], sentries)) {
                    edges.pb(Edge(i, j + n, 1, 1));
                    visible[i][j] = 1;
                } else {
                    visible[i][j] = INF;
                }
            }
        }
        FOR (i, n) {
            FOR (j, n) {
                cout << visible[i][j] << ' ';
            }
            cout << '\n';
        }
        Flow flo(n * 2 + 2, edges);
        ll flow = flo.max_flow(s, t);
        assert(flow == n);
        ll cost = flo.min_cost_flow(s, t, n);
        cout << cost << '\n';
    }

    return 0;
}