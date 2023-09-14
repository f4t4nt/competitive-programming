#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

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

ll dx[] = {0, 1, 0, -1};
ll dy[] = {1, 0, -1, 0};

void solve(ll sx, ll sy, vector<vector<ll>> &grid, vector<ll> &rv) {
    vector<vector<bool>> vis(sz(grid), vector<bool>(sz(grid[0])));
    set<tuple<ll, ll, ll>> cur, adj;
    adj.insert({grid[sx][sy], sx, sy});
    while (sz(adj)) {
        auto it = adj.begin();
        ll x, y, v;
        tie(v, x, y) = *it;
        cur.insert(*it);
        adj.erase(it);
        vis[x][y] = true;
        FOR (i, 4) {
            ll nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < sz(grid) && ny >= 0 && ny < sz(grid[0]) && !vis[nx][ny] && grid[nx][ny] >= grid[sx][sy]) {
                adj.insert({grid[nx][ny], nx, ny});
            }
        }
        ll tmp = get<0>(*cur.rbegin()) - grid[sx][sy];
        rv[sz(cur)] = min(rv[sz(cur)], get<0>(*cur.rbegin()) - grid[sx][sy]);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m, q;
    cin >> n >> m;
    vector<vector<ll>> grid(n, vector<ll>(m));
    FOR (i, n) {
        FOR (j, m) {
            cin >> grid[i][j];
        }
    }
    vector<ll> rv(n * m + 1, 1e18);
    rv[1] = 0;
    FOR (i, n) {
        FOR (j, m) {
            solve(i, j, grid, rv);
        }
    }
    cin >> q;
    while (q--) {
        ll x;
        cin >> x;
        cout << rv[x] << '\n';
    }

    return 0;
}