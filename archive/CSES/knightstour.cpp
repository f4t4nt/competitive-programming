#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

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

int kx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int ky[] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool dfs(int x, int y, int i, vector<vector<int>> &grid) {
    assert(grid[x][y] == 0);
    grid[x][y] = i;
    if (i == 64) {
        return true;
    }
    vector<tuple<int, int, int>> moves;
    FOR (j, 8) {
        int nx = x + kx[j];
        int ny = y + ky[j];
        if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && grid[nx][ny] == 0) {
            int cnt = 0;
            FOR (k, 8) {
                int nnx = nx + kx[k];
                int nny = ny + ky[k];
                if (nnx >= 0 && nnx < 8 && nny >= 0 && nny < 8 && grid[nnx][nny] == 0) {
                    cnt++;
                }
            }
            moves.pb({cnt, nx, ny});
        }
    }
    ssort(moves);
    FORE (move, moves) {
        int nx, ny;
        tie(ignore, nx, ny) = move;
        if (dfs(nx, ny, i + 1, grid)) {
            return true;
        }
        assert(grid[nx][ny] == 0);
        grid[nx][ny] = 0;
    }
    grid[x][y] = 0;
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int x0, y0;
    cin >> y0 >> x0;
    x0--, y0--;
    vector<vector<int>> grid(8, vector<int>(8, 0));
    dfs(x0, y0, 1, grid);
    FOR (i, 8) {
        FOR (j, 8) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}