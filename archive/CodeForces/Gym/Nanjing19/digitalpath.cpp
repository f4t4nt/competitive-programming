#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef string str;
typedef char ch;
typedef long double ld;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define fliip(C) reverse(all(C))
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

const ll MOD = 1e9 + 7;

ll idx = 0;
ll dx[4] = {1, 0, -1, 0};
ll dy[4] = {0, 1, 0, -1};

void dfs(ll i, ll j, ll n, ll m,
vector<vector<ll>> &grid,
vector<vector<vector<ll>>> &dp,
vector<vector<bool>> &vis) {
    if (vis[i][j]) return;
    assert(idx++ < 1e6);
    vis[i][j] = 1;
    FOR (k, 4) {
        ll nx = i + dx[k], ny = j + dy[k];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if (grid[nx][ny] == grid[i][j] + 1) {
            dfs(nx, ny, n, m, grid, dp, vis);
            dp[i][j][1] = (dp[nx][ny][0] + dp[i][j][1]) % MOD;
            dp[i][j][2] = (dp[nx][ny][1] + dp[i][j][2]) % MOD;
            dp[i][j][3] = (dp[nx][ny][2] + dp[nx][ny][3] + dp[i][j][3]) % MOD;
        }
    }
    // cout << i << ' ' << j << ":\n";
    // for (ll x : dp[i][j]) cout << x << ' ';
    // cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m; cin >> n >> m;
    vector<vector<ll>> grid(n, vector<ll>(m));
    vector<vector<vector<ll>>> dp(n,
        vector<vector<ll>>(m,
            vector<ll>(4)));
    vector<vector<bool>> vis(n, vector<bool>(m));
    FOR (i, n) FOR (j, m) cin >> grid[i][j];

    vector<pair<ll, ll>> starts, ends;

    FOR (i, n) FOR (j, m) {
        bool start = true;
        FOR (k, 4) {
            ll ni = dx[k] + i, nj = dy[k] + j;
            if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
            if (grid[ni][nj] + 1 == grid[i][j]) start = false;
        }
        if (start) {
            starts.pb({i, j});
        }
    }

    FOR (i, n) FOR (j, m) {
        bool end = true;
        FOR (k, 4) {
            ll ni = dx[k] + i, nj = dy[k] + j;
            if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
            if (grid[ni][nj] == grid[i][j] + 1) end = false;
        }
        if (end) {
            dp[i][j][0] = 1;
            ends.pb({i, j});
        }
    }

    for (auto [i, j] : starts) {
        dfs(i, j, n, m, grid, dp, vis);
    }

    ll rv = 0;
    for (auto [i, j] : starts) {
        rv += dp[i][j][3];
        rv %= MOD;
    }
    cout << rv << '\n';
}