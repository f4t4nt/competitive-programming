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

// https://codeforces.com/contest/237/problem/E

constexpr ll INF = 1e18;

struct Edge {
    ll s, t, cap, cost;
    Edge (ll s, ll t, ll cap, ll cost) : s(s), t(t), cap(cap), cost(cost) {}
};

struct Flow {
    ll n;
    vector<vector<ll>> adj, cap, cost;

    Flow(ll n, vector<Edge> &edges) : n(n), adj(n), cap(n, vector<ll>(n)), cost(n, vector<ll>(n)) {
        FORE (e, edges) {
            adj[e.s].pb(e.t);
            adj[e.t].pb(e.s);
            cap[e.s][e.t] = e.cap;
            cap[e.t][e.s] = 0;
            cost[e.s][e.t] = e.cost;
        }
    }

    ll bfs(ll s, ll t, vector<ll>& par) {
        fill(all(par), -1);
        par[s] = -2;
        queue<pair<ll, ll>> q;
        q.push({s, INF});
        while (!q.empty()) {
            ll cur = q.front().first;
            ll flow = q.front().second;
            q.pop();
            FORE (next, adj[cur]) {
                if (par[next] == -1 && cap[cur][next]) {
                    par[next] = cur;
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
        auto cap_copy = cap;
        ll flow = 0;
        vector<ll> par(n);
        ll new_flow;
        while (true) {
            new_flow = bfs(s, t, par);
            if (!new_flow) {
                break;
            }
            flow += new_flow;
            ll cur = t;
            while (cur != s) {
                ll prev = par[cur];
                cap[prev][cur] -= new_flow;
                cap[cur][prev] += new_flow;
                cur = prev;
            }
        }
        cap = cap_copy;
        return flow;
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
        auto cap_copy = cap;
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
        cap = cap_copy;
        if (flow < k) {
            return -1;
        } else {
            return cost;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    str t;
    cin >> t;
    vector<vector<ll>> reft(26);
    FOR (i, sz(t)) {
        reft[t[i] - 'a'].pb(i);
    }
    ll n;
    cin >> n;
    vector<pair<str, ll>> s(n);
    FOR (i, n) {
        cin >> s[i].first >> s[i].second;
    }
    // [0, n) - source words
    // [n, n + sz(t)) - target
    // [n + sz(t), n + sz(t) + cnt) - source letters
    // n + sz(t) + cnt - source
    // n + sz(t) + cnt + 1 - target
    ll cnt = 0;
    vector<Edge> edges;
    FOR (i, n) {
        FORE (c, s[i].first) {
            edges.pb({i, n + sz(t) + cnt, 1, 0});
            cout << "word " << i << " -> letter " << c << " cap 1 cost 0\n";
            FORE (j, reft[c - 'a']) {
                edges.pb({n + sz(t) + cnt, n + j, 1, i + 1});
                cout << "letter " << c << " -> target " << j << " cap 1 cost " << i + 1 << '\n';
            }
            cnt++;
        }
    }
    ll source = n + sz(t) + cnt, target = source + 1;
    FOR (i, sz(t)) {
        edges.pb({n + i, target, 1, 0});
        cout << "target " << i << " -> sink cap 1 cost 0\n";
    }
    FOR (i, n) {
        edges.pb({source, i, s[i].second, 0});
        cout << "source -> word " << i << " cap " << s[i].second << " cost 0\n";
    }
    Flow f(target + 1, edges);
    ll flow = f.max_flow(source, target), rv = f.min_cost_flow(source, target, sz(t));
    if (flow == sz(t)) {
        rv = f.min_cost_flow(source, target, sz(t));
    } else {
        assert(rv == -1);
    }
    cout << rv << '\n';

    return 0;
}