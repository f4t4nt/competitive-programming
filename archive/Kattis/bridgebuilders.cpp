#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
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

ll dx[] = {0, 0, -1, 1};
ll dy[] = {-1, 1, 0, 0};

vector<ll> get_dist_forest(
    ll xs, ll ys,
    vector<str> &grid,
    vector<vector<ll>> &dist,
    vector<vector<bool>> &vis,
    map<pair<ll, ll>, ll> &forest_ids
) {
    vector<ll> rv(sz(forest_ids), 1e18);
    queue<pair<ll, ll>> q;
    q.push({xs, ys});
    dist[xs][ys] = 0;
    vis[xs][ys] = true;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (grid[x][y] == 'T') {
            rv[forest_ids[{x, y}]] = dist[x][y];
        }
        FOR (i, 4) {
            ll nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < sz(grid) && ny >= 0 && ny < sz(grid[0]) &&
                grid[nx][ny] != '.' && !vis[nx][ny])
            {
                dist[nx][ny] = dist[x][y] + 1;
                vis[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }
    return rv;
}

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

vector<tuple<ll, ll, ll>> get_mst_forest(ll n, vector<tuple<ll, ll, ll>> &edges_forest) {
    DSU dsu(n);
    vector<tuple<ll, ll, ll>> rv;
    ssort(edges_forest);
    FORE (e, edges_forest) {
        auto [w, u, v] = e;
        if (dsu.unite(u, v)) {
            rv.pb(e);
        }
    }
    return rv;
}

vector<pair<ll, ll>> connect_forest(
    ll xs, ll ys,
    ll xt, ll yt,
    vector<str> &grid,
    vector<vector<ll>> &dist,
    vector<vector<bool>> &vis
) {
    vector<vector<pair<ll, ll>>> prev(sz(grid), vector<pair<ll, ll>>(sz(grid[0])));
    queue<pair<ll, ll>> q;
    q.push({xs, ys});
    vis[xs][ys] = true;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (x == xt && y == yt) {
            vector<pair<ll, ll>> rv;
            while (x != xs || y != ys) {
                rv.pb({x, y});
                auto [nx, ny] = prev[x][y];
                x = nx;
                y = ny;
            }
            return rv;
        }
        FOR (i, 4) {
            ll nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < sz(grid) && ny >= 0 && ny < sz(grid[0]) &&
                grid[nx][ny] != '.' && !vis[nx][ny])
            {
                dist[nx][ny] = min(dist[nx][ny], dist[x][y] + 1);
                vis[nx][ny] = true;
                prev[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }
    pair<ll, ll> p = {xt, yt};
    vector<pair<ll, ll>> rv;
    while (p.first != xs || p.second != ys) {
        rv.pb(p);
        p = prev[p.first][p.second];
    }
    return rv;
}

void init_connect(
    ll u,
    ll par,
    vector<str> &grid,
    vector<pair<ll, ll>> &forests,
    vector<vector<pair<ll, ll>>> &connections_forest,
    vector<vector<ll>> &dist,
    vector<vector<bool>> &vis
) {
    FORE (e, connections_forest[u]) {
        auto [v, w] = e;
        if (v != par) {
            vis = vector<vector<bool>>(sz(grid), vector<bool>(sz(grid[0])));
            vector<vector<ll>> dist1(sz(grid), vector<ll>(sz(grid[0]), 1e18));
            dist1[forests[u].first][forests[u].second] = 0;
            auto path = connect_forest(forests[u].first, forests[u].second, forests[v].first, forests[v].second, grid, dist1, vis);
            FORE (p, path) {
                auto [x, y] = p;
                if (dist[x][y] == 1e18) {
                    dist[x][y] = dist1[x][y];
                }
            }
            init_connect(v, u, grid, forests, connections_forest, dist, vis);
        }
    }
}

void full_connect(
    vector<str> &grid,
    vector<pair<ll, ll>> &forests,
    vector<vector<ll>> &dist
) {
    queue<pair<ll, ll>> q;
    FORE (e, forests) {
        q.push(e);
        dist[e.first][e.second] = 0;
    }
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        FOR (i, 4) {
            ll nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < sz(dist) && ny >= 0 && ny < sz(dist[0]) &&
                grid[nx][ny] != '.' && dist[nx][ny] == 1e18)
            {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll T;
    cin >> T;
    FOR (t, T) {
        ll n, m, rv = 0;
        cin >> n >> m;
        vector<str> grid(n);
        FOR (i, n) {
            cin >> grid[i];
        }
        map<pair<ll, ll>, ll> forest_ids;
        vector<pair<ll, ll>> forests;
        FOR (i, n) {
            FOR (j, m) {
                if (grid[i][j] == 'T') {
                    forest_ids[{i, j}] = sz(forest_ids);
                    forests.pb({i, j});
                }
            }
        }
        vector<tuple<ll, ll, ll>> edges_forest;
        vector<vector<ll>> dist_forest(sz(forest_ids));
        vector<vector<ll>> dist;
        vector<vector<bool>> vis;
        FORE (e, forest_ids) {
            dist = vector<vector<ll>>(n, vector<ll>(m, 1e18));
            vis = vector<vector<bool>>(n, vector<bool>(m));
            auto [x, y] = e.first;
            ll u = e.second;
            dist_forest[u] = get_dist_forest(x, y, grid, dist, vis, forest_ids);
            FOR (v, u) {
                edges_forest.pb({dist_forest[u][v], u, v});
            }
        }
        ssort(edges_forest);
        auto mst_forest = get_mst_forest(sz(forest_ids), edges_forest);
        vector<vector<pair<ll, ll>>> connections_forest(sz(forest_ids));
        FORE (e, mst_forest) {
            auto [w, u, v] = e;
            connections_forest[u].pb({v, w});
            connections_forest[v].pb({u, w});
        }
        dist = vector<vector<ll>>(n, vector<ll>(m, 1e18));
        dist[0][0] = 0;
        init_connect(0, -1, grid, forests, connections_forest, dist, vis);
        vector<vector<ll>> full_dist(n, vector<ll>(m, 1e18));
        full_connect(grid, forests, full_dist);
        FOR (i, n) {
            FOR (j, m) {
                if (dist[i][j] == 1e18) {
                    if (grid[i][j] == '.') {
                        dist[i][j] = 0;
                    } else {
                        dist[i][j] = full_dist[i][j];
                    }
                }
            }
        }
        FOR (i, n) {
            FOR (j, m) {
                rv += dist[i][j];
            }
        }
        cout << "Case #" << t + 1 << ": " << rv << '\n';
    }

    return 0;
}