#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

ll dx[] = {1, 0, -1, 0};
ll dy[] = {0, 1, 0, -1};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m; cin >> n >> m;
    vector<str> grid(n);
    FOR (i, n) cin >> grid[i];
    vector<vector<ll>> dist(n, vector<ll>(m, LLONG_MAX));
    queue<pair<ll, ll>> bfs;
    FOR (i, n) FOR (j, m) if (grid[i][j] == '.') {
        dist[i][j] = 0;
        bfs.push({i, j});
    }
    FOR (i, n) {
        bfs.push({i, -1});
        bfs.push({i, m});
    }
    FOR (j, m) {
        bfs.push({-1, j});
        bfs.push({n, j});
    }
    ll mx = 0;
    while (!bfs.empty()) {
        ll i, j; tie(i, j) = bfs.front();
        bfs.pop();
        FOR (k, 4) {
            ll ni = i + dx[k], nj = j + dy[k];
            if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
            if (dist[ni][nj] != LLONG_MAX) continue;
            if (i == -1 || i == n || j == -1 || j == m) {
                dist[ni][nj] = 1;
            } else {
                dist[ni][nj] = dist[i][j] + 1;
            }
            mx = max(mx, dist[ni][nj]);
            bfs.push({ni, nj}); 
        }
    }
    vector<str> rv(n);
    if (mx < 10) {
        FOR (i, n) FOR (j, m) {
            if (dist[i][j] == 0) {
                rv[i] += "..";
            } else {
                rv[i] += "." + to_string(dist[i][j]);
            }
        }
    } else {
        FOR (i, n) FOR (j, m) {
            if (dist[i][j] == 0) {
                rv[i] += "...";
            } elif (dist[i][j] < 10) {
                rv[i] += ".." + to_string(dist[i][j]);
            } else {
                rv[i] += "." + to_string(dist[i][j]);
            }
        }
    }
    FOR (i, n) cout << rv[i] << '\n';

    return 0;
}