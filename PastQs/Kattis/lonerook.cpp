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

ll dxs[4] = {1, -1, 0, 0};
ll dys[4] = {0, 0, 1, -1};
ll knight_x[8] = {2, 1, -1, -2, -2, -1, 1, 2};
ll knight_y[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool reachable(ll dx, ll dy, ll x, ll y, ll &n, ll &m,
    vector<vector<ch>> &grid,
    vector<vector<ll>> &visited)
{
    while (x >= 0 && y >= 0 && x < n && y < m && grid[x][y] != 'K') {
        if (visited[x][y] > 0) {
            return true;
        }
        x += dx;
        y += dy;
    }
    return false;
}

void update_q(ll dx, ll dy, ll x, ll y, ll &n, ll &m,
    queue<pair<ll, ll>> &q,
    vector<vector<ch>> &grid,
    vector<vector<ll>> &visited,
    vector<vector<ll>> &defended)
{
    while (x >= 0 && y >= 0 && x < n && y < m && (defended[x][y] == 0 || grid[x][y] != 'K')) {
        assert(defended[x][y] >= 0);
        if (visited[x][y] < 1 && defended[x][y] == 0) {
            q.push(mp(x, y));
            visited[x][y]++;
            if (grid[x][y] == 'K') {
                grid[x][y] = '.';
                FOR (k, 8) {
                    ll x2 = x + knight_x[k];
                    ll y2 = y + knight_y[k];
                    if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < m) {
                        defended[x2][y2]--;
                        if (defended[x2][y2] == 0) {
                            FOR (i, 4) {
                                ll dx = dxs[i];
                                ll dy = dys[i];
                                if (reachable(dx, dy, x2, y2, n, m, grid, visited)) {
                                    q.push(mp(x2, y2));
                                    visited[x2][y2]++;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        x += dx;
        y += dy;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    pair<ll, ll> start, end;
    vector<vector<ch>> grid(n, vector<ch>(m));
    vector<vector<ll>> defended(n, vector<ll>(m));
    FOR (i, n) {
        FOR (j, m) {
            cin >> grid[i][j];
            if (grid[i][j] == 'R') {
                start = mp(i, j);
            } elif (grid[i][j] == 'T') {
                end = mp(i, j);
            } elif (grid[i][j] == 'K') {
                FOR (k, 8) {
                    ll x = i + knight_x[k];
                    ll y = j + knight_y[k];
                    if (x >= 0 && x < n && y >= 0 && y < m) {
                        defended[x][y]++;
                    }
                }
            }
        }
    }

    vector<vector<ll>> visited(n, vector<ll>(m));
    queue<pair<ll, ll>> q;
    q.push(start);
    visited[start.first][start.second] = 1;
    while (!q.empty()) {
        pair<ll, ll> cur = q.front();
        q.pop();
        if (cur == end) {
            cout << "yes\n";
            return 0;
        }
        update_q(1, 0, cur.first, cur.second, n, m, q, grid, visited, defended);
        update_q(-1, 0, cur.first, cur.second, n, m, q, grid, visited, defended);
        update_q(0, 1, cur.first, cur.second, n, m, q, grid, visited, defended);
        update_q(0, -1, cur.first, cur.second, n, m, q, grid, visited, defended);
    }

    cout << "no\n";

    return 0;
}