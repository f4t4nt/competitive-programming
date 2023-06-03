#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
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

constexpr ll INF = 1e15;
constexpr ll LOG2D = 20;

struct DSU {
    ll cnt;
    vector<ll> e;
    DSU(ll n) { e = vector<ll>(n, -1); cnt = n; }
    void reset() { e = vector<ll>(sz(e), -1); cnt = sz(e); }
    ll get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool same_set(ll a, ll b) { return get(a) == get(b); }
    ll size(ll x) { return -e[get(x)]; }
    ll count() { return cnt; }
    bool unite(ll x, ll y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y]; e[y] = x;
        cnt--;
        return true;
    }
};

void gen_tree(
    ll u,
    vector<vector<pair<ll, ll>>> &adj,
    vector<pair<ll, ll>> &parent,
    vector<ll> &depth,
    vector<ll> &pre,
    vector<ll> &post,
    ll &idx,
    ll d = 0
) {
    depth[u] = d;
    pre[u] = idx++;
    FORE (elem, adj[u]) {
        ll v, t;
        tie(v, t) = elem;
        if (v != parent[u].first) {
            parent[v] = {u, t};
            gen_tree(v, adj, parent, depth, pre, post, idx, d + 1);
        }
    }
    post[u] = idx++;
}

pair<ll, ll> jump(
    ll u,
    ll d,
    vector<vector<pair<ll, ll>>> &anc
) {
    ll dist = 0;
    FORR (i, LOG2D) {
        if (d & (1 << i)) {
            dist += anc[u][i].second;
            u = anc[u][i].first;
        }
    }
    return {u, dist};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, l;
    cin >> n;
    DSU dsu(n);
    tuple<ll, ll, ll> tmp;
    vector<vector<pair<ll, ll>>> adj(n);
    FOR (i, n) {
        ll j, t;
        cin >> j >> t;
        j--;
        adj[i].pb({j, t});
        adj[j].pb({i, t});
        if (!dsu.unite(i, j)) {
            tmp = {t, i, j};
        }
    }
    cin >> l;
    vector<tuple<ll, ll, ll>> cpt(l);
    map<ll, vector<ll>> imp_dist;
    FOR (i, l) {
        ll u, v, t;
        cin >> u >> v >> t;
        u--, v--;
        imp_dist[u] = vector<ll>(n, INF);
        cpt[i] = {t, u, v};
        adj[u].pb({v, t});
        adj[v].pb({u, t});
        // dsu.unite(u, v);
    }
    imp_dist[get<1>(tmp)] = vector<ll>(n, INF);
    cpt.pb(tmp);

    FORE (elem, imp_dist) {
        ll u0 = elem.first;
        vector<ll> &dist = elem.second;
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
        pq.push({0, u0});
        dist[u0] = 0;
        while (!pq.empty()) {
            ll d, u;
            tie(d, u) = pq.top();
            pq.pop();
            if (d > dist[u]) continue;
            FORE (elem, adj[u]) {
                ll v, t;
                tie(v, t) = elem;
                if (dist[v] > dist[u] + t) {
                    dist[v] = dist[u] + t;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    FORE (edge, cpt) {
        ll t, u, v;
        tie(t, u, v) = edge;
        FOR (i, sz(adj[u])) {
            if (adj[u][i].first == v && adj[u][i].second == t) {
                adj[u].erase(adj[u].begin() + i);
                break;
            }
        }
        FOR (i, sz(adj[v])) {
            if (adj[v][i].first == u && adj[v][i].second == t) {
                adj[v].erase(adj[v].begin() + i);
                break;
            }
        }
    }

    ll idx = 0;
    vector<pair<ll, ll>> parent(n, {-1, INF});
    vector<ll> depth(n), pre(n), post(n);
    FOR (i, n) {
        if (parent[i].first == -1) {
            gen_tree(i, adj, parent, depth, pre, post, idx);
        }
    }

    vector<vector<pair<ll, ll>>> anc(n, vector<pair<ll, ll>>(LOG2D, {-1, INF}));
    FOR (i, n) {
        anc[i][0] = parent[i];
    }
    FOB (i, 1, n) {
        FOR (v, n) {
            anc[v][i] = anc[anc[v][i - 1].first][i - 1];
        }
    }

    ll t;
    cin >> t;
    while (t--) {
        ll a, b, rv = INF;
        cin >> a >> b;
        if (dsu.same_set(a, b)) {
            if (depth[a] > depth[b]) {
                swap(a, b);
            }
            ll dist, d = depth[b] - depth[a];
            tie(b, dist) = jump(b, d, anc);
            if (a == b) {
                cout << dist << '\n';
                continue;
            }
            FORR (i, LOG2D) {
                if (anc[a][i].first != anc[b][i].first) {
                    dist += anc[a][i].second + anc[b][i].second;
                    a = anc[a][i].first;
                    b = anc[b][i].first;
                }
            }
            dist += anc[a][0].second + anc[b][0].second;
            rv = dist;
        }
        FORE (dist, imp_dist) {
            rv = min(rv, dist.second[a] + dist.second[b]);
        }
        if (rv == INF) {
            cout << -1 << '\n';
        } else {
            cout << rv << '\n';
        }
    }

    return 0;
}