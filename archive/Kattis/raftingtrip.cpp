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
#define sz(C) (int) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(int x = 0; x < (int) e; x++)
#define FORR(x, e) for(int x = (int) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(int x = 0; x < (int) e; x += (int) i)
#define FOBI(x, b, e, i) for(int x = (int) b; x < (int) e; x += (int) i)
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

ll r, c;
ch grid[500][500];
ll dx[] = {0, 0, -1, 1};
ll dy[] = {-1, 1, 0, 0};

bool in_range(ll x, ll y) {
    return x >= 0 && x < r && y >= 0 && y < c;
}

bool is_land(ll x, ll y) {
    return !in_range(x, y) || grid[x][y] == '#' || grid[x][y] == '.';
}

bool is_land(ll i) {
    return grid[i / c][i % c] == '#' || grid[i / c][i % c] == '.';
}

bool is_spot(ll x, ll y) {
    return in_range(x, y) && grid[x][y] == '#';
}

bool is_spot(ll i) {
    return grid[i / c][i % c] == '.';
}

ll hash_(ll x, ll y) {
    return x * c + y;
}

void dfs(ll &rv, ll u, set<ll> &spots, vector<vector<ll>> &adj, vector<set<ll>> &adj_spot) {
    set<ll> add_spots;
    FORE (x, adj_spot[u]) {
        if (spots.find(x) == spots.end()) {
            spots.insert(x);
            add_spots.insert(x);
        }
    }
    rv = max(rv, (ll) sz(spots));
    FORE (v, adj[u]) {
        dfs(rv, v, spots, adj, adj_spot);
    }
    FORE (x, add_spots) {
        spots.erase(x);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> r >> c;
    FOR (i, r) {
        FOR (j, c) {
            cin >> grid[i][j];
        }
    }

    vector<vector<ll>> adj(r * c);
    FOR (i, r) {
        FOR (j, c) {
            if (is_land(i, j)) {
                continue;
            } elif (grid[i][j] == '^' && !is_land(i - 1, j)) {
                adj[hash_(i, j)].pb(hash_(i - 1, j));
            } elif (grid[i][j] == 'v' && !is_land(i + 1, j)) {
                adj[hash_(i, j)].pb(hash_(i + 1, j));
            } elif (grid[i][j] == '<' && !is_land(i, j - 1)) {
                adj[hash_(i, j)].pb(hash_(i, j - 1));
            } elif (grid[i][j] == '>' && !is_land(i, j + 1)) {
                adj[hash_(i, j)].pb(hash_(i, j + 1));
            }
        }
    }

    vector<vector<ll>> rev_adj(r * c);
    FOR (i, r * c) {
        FORE (v, adj[i]) {
            rev_adj[v].pb(i);
        }
    }

    vector<ll> in(r * c);
    FOR (i, r * c) {
        if (is_land(i)) {
            continue;
        }
        FORE (v, adj[i]) {
            in[v]++;
        }
    }

    queue<ll> q;
    FOR (i, r * c) {
        if (!is_land(i) && in[i] == 0) {
            q.push(i);
        }
    }

    vector<ll> tmp;
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        tmp.pb(u);
        FORE (v, adj[u]) {
            in[v]--;
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }

    vector<set<ll>> cycles;
    vector<bool> vis(r * c);
    FOR (i, r * c) {
        if (vis[i] || is_land(i) || in[i] == 0) {
            continue;
        }
        set<ll> cycle;
        ll u = i;
        while (!vis[u]) {
            vis[u] = true;
            cycle.insert(u);
            u = adj[u][0];
        }
        cycles.pb(cycle);
    }

    vector<set<ll>> adj_spot(r * c);
    FOR (i, r) {
        FOR (j, c) {
            if (is_land(i, j)) {
                continue;
            }
            FOR (k, 4) {
                ll x = i + dx[k];
                ll y = j + dy[k];
                if (is_spot(x, y)) {
                    adj_spot[hash_(i, j)].insert(hash_(x, y));
                }
            }
        }
    }

    FORE (cycle, cycles) {
        set<ll> cycle_spot;
        FORE (u, cycle) {
            FORE (v, rev_adj[u]) {
                adj[v].erase(find(all(adj[v]), u));
                if (cycle.count(v)) {
                    continue;
                }
                adj[v].pb(sz(adj));
            }
            FORE (v, adj_spot[u]) {
                cycle_spot.insert(v);
            }
        }
        adj.pb({});
        adj_spot.pb(cycle_spot);
    }

    rev_adj = vector<vector<ll>>(sz(adj));
    FOR (i, sz(adj)) {
        FORE (v, adj[i]) {
            rev_adj[v].pb(i);
        }
    }

    ll rv = 0;
    set<ll> spots;
    FOR (i, sz(adj)) {
        if (is_land(i) || sz(adj[i]) > 0) {
            continue;
        }
        dfs(rv, i, spots, rev_adj, adj_spot);
    }
    cout << rv << '\n';

    return 0;
}