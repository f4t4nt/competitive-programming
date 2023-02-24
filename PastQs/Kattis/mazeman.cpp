#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

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
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

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

ll dx[4] = {-1, 0, 1, 0};
ll dy[4] = {0, -1, 0, 1};

ll bfs(ll &x0, ll &y0, ll &n, ll &m, vector<vector<ch>> &grid) {
    ll rv = 0;
    ch player = grid[x0][y0];
    queue<pair<ll, ll>> q;
    q.push({x0, y0});
    while (!q.empty()) {
        ll x, y;
        tie(x, y) = q.front();
        q.pop();
        FOR (i, 4) {
            ll x1 = x + dx[i], y1 = y + dy[i];
            if (x1 >= 0 && x1 < n && y1 >= 0 && y1 < m) {
                if (grid[x1][y1] == ' ') {
                    grid[x1][y1] = player;
                    q.push({x1, y1});
                } elif (grid[x1][y1] == '.') {
                    rv++;
                    grid[x1][y1] = player;
                    q.push({x1, y1});
                }
            }
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    str line;
    getline(cin, line);
    istringstream iss(line);
    ll n, m, total = 0;
    iss >> n >> m;
    vector<vector<pair<ll, ll>>> doors(26);
    vector<vector<ch>> grid(n, vector<ch>(m));
    FOR (i, n) {
        getline(cin, line);
        FOR (j, m) {
            grid[i][j] = line[j];
            if (line[j] >= 'A' && line[j] <= 'W') {
                doors[line[j] - 'A'].pb({i, j});
            } elif (line[j] == '.') {
                total++;
            }
        }
    }

    ll rv = 0;
    FOR (i, 26) {
        ll tmp = 0;
        FORE (door, doors[i]) {
            tmp += bfs(door.first, door.second, n, m, grid);
        }
        if (tmp > 0) {
            rv++;
            total -= tmp;
        }
    }

    cout << rv << ' ' << total << '\n';
    // FOR (i, n) {
    //     FOR (j, m) {
    //         cout << grid[i][j];
    //     }
    //     cout << '\n';
    // }

    return 0;
}