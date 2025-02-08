#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
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
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m; cin >> n >> m;
    vector<str> grid(n);
    FOR (i, n) cin >> grid[i];
    FOR (i, n) FOR (j, m) {
        if (grid[i][j] == 'C') {
            FOR (k, 4) {
                ll x = i + dx[k], y = j + dy[k];
                if (x < 0 || x >= n || y < 0 || y >= m) continue;
                if (grid[x][y] == 'L') {
                    grid[i][j] = 'W';
                    break;
                }
            }
        }
    }

    ll ans = 0;
    auto dfs = [&](auto &&self, ll i, ll j) -> void {
        if (i < 0 || i >= n || j < 0 || j >= m) return;
        if (grid[i][j] == 'L') grid[i][j] = 'X';
        else return;
        FOR (k, 4) self(self, i + dx[k], j + dy[k]);
    };
    FOR (i, n) FOR (j, m) if (grid[i][j] == 'L') {
        ans++;
        dfs(dfs, i, j);
    }

    map<pll, ll> id;
    FOR (i, n) FOR (j, m) if (grid[i][j] == 'C') id[{i, j}] = sz(id);
    vector<vector<ll>> adj(sz(id));
    FOR (i, n) FOR (j, m) if (grid[i][j] == 'C' && (i + j) % 2 == 0) {
        FOR (k, 4) {
            ll x = i + dx[k], y = j + dy[k];
            if (x < 0 || x >= n || y < 0 || y >= m) continue;
            if (grid[x][y] == 'C') adj[id[{i, j}]].pb(id[{x, y}]);
        }
    }

    vector<ll> matching(sz(id), -1);
    vector<bool> vis_lhs(sz(id)), vis_rhs(sz(id));

    FOR (u, sz(id)) {
        for (ll v : adj[u]) {
            if (matching[v] == -1) {
                matching[v] = u;
                vis_lhs[u] = true;
                break;
            }
        }
    }

    function<bool(ll)> bpm = [&](ll u) {
        for (ll v : adj[u]) {
            if (!vis_rhs[v]) {
                vis_rhs[v] = true;
                if (matching[v] == -1 || bpm(matching[v])) {
                    matching[v] = u;
                    return true;
                }
            }
        }
        return false;
    };

    FOR (u, sz(id)) if (!vis_lhs[u]) {
        fill(all(vis_rhs), false);
        bpm(u);
    }

    FOR (u, sz(id)) if (matching[u] == -1) ans++;

    cout << ans << '\n';

    return 0;
}