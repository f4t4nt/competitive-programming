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

ll treasure_count(ll x1, ll y1, ll x2, ll y2, vector<vector<ll>> &treasure_counts) {
    return treasure_counts[x2][y2] - treasure_counts[x1][y2] - treasure_counts[x2][y1] + treasure_counts[x1][y1];
}

pair<ll, ll> find_next(vector<vector<ch>> &grid) {
    FOR (i, sz(grid)) {
        FOR (j, sz(grid[i])) {
            if (grid[i][j] == '.' || grid[i][j] == '$') {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

void print_grid(vector<vector<ch>> &grid) {
    FOR (i, sz(grid)) {
        FOR (j, sz(grid[i])) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}

bool dfs_solve(ch cur_ch, ll x, ll y, ll &n, ll &m, vector<vector<ch>> &grid, vector<vector<ll>> &treasure_counts) {
    ch next_ch = cur_ch + 1;
    if (cur_ch == 'Z') {
        next_ch = 'a';
    }

    ll side_len = 1;
    
    while (x + side_len <= n && y + side_len <= m &&
        treasure_count(x, y, x + side_len, y + side_len, treasure_counts) == 0) {
        side_len++;
    }

    pair<ll, ll> treasure_pos = {-1, -1};
    while (x + side_len <= n && y + side_len <= m &&
        treasure_count(x, y, x + side_len, y + side_len, treasure_counts) == 1) {
        bool invalid = false;
        FOB (i, x, x + side_len) {
            FOB (j, y, y + side_len) {
                if (grid[i][j] == '$') {
                    treasure_pos = {i, j};
                } elif (grid[i][j] != '.' && grid[i][j] != cur_ch) {
                    invalid = true;
                    break;
                }
                grid[i][j] = cur_ch;
            }
            if (invalid) {
                break;
            }
        }
        if (invalid) {
            break;
        }
        ll next_x, next_y;
        tie(next_x, next_y) = find_next(grid);
        if (next_x == -1) {
            return true;
        }
        if (cur_ch == 'z') {
            return false;
        }
        if (dfs_solve(next_ch, next_x, next_y, n, m, grid, treasure_counts)) {
            return true;
        }
        side_len++;
    }

    FOR (i, n) {
        FOR (j, m) {
            if (grid[i][j] == cur_ch) {
                grid[i][j] = '.';
            }
            if (i == treasure_pos.first && j == treasure_pos.second) {
                grid[i][j] = '$';
            }
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<vector<ch>> grid(n, vector<ch>(m));
    vector<vector<ll>> treasure_counts(n + 1, vector<ll>(m + 1));
    FOR (i, n) {
        FOR (j, m) {
            cin >> grid[i][j];
        }
    }
    FOB (i, 1, n + 1) {
        FOB (j, 1, m + 1) {
            treasure_counts[i][j] = treasure_counts[i - 1][j] + treasure_counts[i][j - 1] - treasure_counts[i - 1][j - 1];
            if (grid[i - 1][j - 1] == '$') {
                treasure_counts[i][j]++;
            }
        }
    }
    ll x, y;
    tie(x, y) = find_next(grid);
    if (dfs_solve('A', x, y, n, m, grid, treasure_counts)) {
        print_grid(grid);
    } else {
        cout << "elgnatcer\n";
    }

    return 0;
}