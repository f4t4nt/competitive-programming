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
    pld,
    null_type,
    less<pld>,
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        vector<vector<ll>> rock(n, vector<ll>(m, 1e18)), dist = rock;
        FOR (i, n) FOR (j, m) cin >> rock[i][j];
        queue<pll> bfs;
        bfs.push({0, 0});
        dist[0][0] = 0;
        while (!bfs.empty()) {
            auto [x, y] = bfs.front(); bfs.pop();
            ll nx = (x + 1) % n, nnx = (x + 2) % n, ny = y + 1;
            if (!rock[nx][y] && !rock[nnx][y]) {
                if (dist[nnx][y] > dist[x][y] + 1) {
                    dist[nnx][y] = dist[x][y] + 1;
                    bfs.push({nnx, y});
                }
            }
            if (ny < m && !rock[nx][ny]) {
                if (dist[nx][ny] > dist[x][y] + 1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    bfs.push({nx, ny});
                }
            }
        }
        ll ans = 1e18;
        FOR (i, n) {
            ll d = dist[i][m - 1];
            if (d == 1e18) continue;
            ll cur_end = (n - 1 + d) % n,
                go_up = (n - i + cur_end) % n,
                go_down = (i + n - cur_end) % n;
            ans = min(ans, d + min(go_up, go_down));
        }
        cout << (ans == 1e18 ? -1 : ans) << '\n';
    }

    return 0;
}