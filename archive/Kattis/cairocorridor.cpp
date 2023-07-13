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

vector<ll> adjp[2][2][5] = {
    { // a
        { // even
            {1, 0, -1},
            {0, 0, -1},
            {1, -1, 0},
            {1, 0, 0},
            {0, 1, 0},
        },
        { // odd
            {1, 0, -1},
            {0, -1, 0},
            {1, -1, 0},
            {0, 0, 1},
            {1, 0, 0},
        },
    },
    { // b
        { // even
            {0, 0, 0},
            {1, -1, 0},
            {0, 0, 1},
            {1, 0, 1},
            {0, 1, 0},
        },
        { // odd
            {1, 0, -1},
            {0, 0, 0},
            {0, 0, 1},
            {1, 1, 0},
            {0, 1, 0},
        },
    },
};

struct Tile {
    // id, type, orientation, fill, x, y, mask
    ll id, t, s, f, x, y, mask;
    // adj list of ids
    vector<ll> adj;
};

ll dfs(ll id, vector<Tile> &tiles, vector<bool> &vis, vector<vector<ll>> &degs, bool skip = false) {
    vis[id] = true;
    ll mask = 0, deg = sz(tiles[id].adj);
    if (!skip) {
        mask = tiles[id].mask;
    }
    FORE (nxt, tiles[id].adj) {
        if (vis[nxt]) {
            continue;
        }
        if (tiles[nxt].f) {
            deg--;
            continue;
        }
        mask |= dfs(nxt, tiles, vis, degs);
        if (skip) {
            break;
        }
    }
    degs[deg].pb(id);
    return mask;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n, m;
        cin >> n >> m;
        vector<str> grid(n);
        FOR (i, n) {
            cin >> grid[i];
        }
        ll t = 0, id = 0;
        map<vector<ll>, ll> tile_id;
        vector<Tile> tiles;
        FOR (i, n) {
            FOR (j2, 2 * m) {
                ll j = j2 / 2, s = (i + j) % 2, f = (grid[i][j2] == '1'), mask = 0;
                tile_id[{t, i, j}] = id;
                // top 1, right 2, bottom 4, left 8
                if (i == 0 && (t == 0 || s == 0)) {
                    mask |= 1;
                }
                if (j == m - 1 && (t == 1 || s == 1)) {
                    mask |= 2;
                }
                if (i == n - 1 && (t == 1 || s == 0)) {
                    mask |= 4;
                }
                if (j == 0 && (t == 0 || s == 1)) {
                    mask |= 8;
                }
                tiles.pb({id, t, s, f, i, j, mask});
                t = 1 - t;
                id++;
            }
        }
        FORE (tile, tiles) {
            ll t = tile.t, s = tile.s, i = tile.x, j = tile.y;
            if (tile.f) {
                continue;
            }
            FOR (k, 5) {
                ll nt = adjp[t][s][k][0], ni = i + adjp[t][s][k][1], nj = j + adjp[t][s][k][2];
                if (tile_id.count({nt, ni, nj})) {
                    ll nxt = tile_id[{nt, ni, nj}];
                    if (!tiles[nxt].f) {
                        tile.adj.pb(nxt);
                    }
                }
            }
        }
        vector<bool> vis(id);
        vector<vector<ll>> degs;
        ll src = -1;
        FOR (i, id) {
            if (!vis[i] && !tiles[i].f) {
                degs = vector<vector<ll>>(6);
                ll mask = dfs(i, tiles, vis, degs);
                if (mask == 15) {
                    src = i;
                    break;
                }
            }
        }
        if (src == -1) {
            cout << "NO MINIMAL CORRIDOR\n";
            continue;
        }
        // at most 4 nodes with deg 1
        if (sz(degs[1]) > 4) {
            cout << "NO MINIMAL CORRIDOR\n";
            continue;
        }
        // at most 6 nodes with deg >= 3
        if (sz(degs[3]) + sz(degs[4]) + sz(degs[5]) > 6) {
            cout << "NO MINIMAL CORRIDOR\n";
            continue;
        }
        ll rv = 0;
        vector<ll> ref;
        FOR (deg, 6) {
            rv += sz(degs[deg]);
            if (deg == 0) {
                assert(sz(degs[deg]) == 0);
            }
            if (deg == 2) {
                FORE (i, degs[deg]) {
                    if (tiles[i].mask != 0) {
                        ref.pb(i);
                    }
                }
                continue;
            }
            FORE (i, degs[deg]) {
                ref.pb(i);
            }
        }
        bool ok = true;
        FORE (i, ref) {
            tiles[i].f = 1;
            vis = vector<bool>(id);
            degs = vector<vector<ll>>(6);
            ll mask = dfs(i, tiles, vis, degs, true);
            if (mask == 15) {
                ok = false;
                break;
            }
            tiles[i].f = 0;
        }
        if (!ok) {
            cout << "NO MINIMAL CORRIDOR\n";
            continue;
        }
        cout << rv << '\n';
    }

    return 0;
}