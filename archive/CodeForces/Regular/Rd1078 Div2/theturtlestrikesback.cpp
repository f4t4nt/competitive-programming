#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
// s.order_of_key(x) -> number of elements < x
// s.find_by_order(x) -> iterator to the x-th element (0-indexed)

#pragma GCC target("popcnt,lzcnt")
// __builtin_popcount(x) -> number of set bits
// __builtin_clz(x) -> number of leading zeros
// for ll, use __builtin_popcountll, __builtin_clzll

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

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
        const ll NEG = -2e18;
        vector<vector<ll>> grid(n + 2, vector<ll>(m + 2, 0)),
            dp_src(n + 2, vector<ll>(m + 2, NEG)),
            dp_dst(n + 2, vector<ll>(m + 2, NEG)),
            row_pre(n + 2, vector<ll>(m + 2, NEG)),
            col_pre(n + 2, vector<ll>(m + 2, NEG));
        vector<vector<pll>> prv(n + 2, vector<pll>(m + 2));

        for (ll i = 1; i <= n; i++)
            for (ll j = 1; j <= m; j++)
                cin >> grid[i][j];

        // dpS[i][j] = max path sum from (1,1) to (i,j)
        for (ll i = 1; i <= n; i++)
            for (ll j = 1; j <= m; j++) {
                if (i == 1 && j == 1) {
                    dp_src[i][j] = grid[i][j];
                } elif (dp_src[i - 1][j] > dp_src[i][j - 1]) {
                    dp_src[i][j] = dp_src[i - 1][j] + grid[i][j];
                    prv[i][j] = {i - 1, j};
                } else {
                    dp_src[i][j] = dp_src[i][j - 1] + grid[i][j];
                    prv[i][j] = {i, j - 1};
                }
            }

        ll mx = dp_src[n][m];

        // dpT[i][j] = max path sum from (i,j) to (n,m)
        for (ll i = n; i >= 1; i--)
            for (ll j = m; j >= 1; j--) {
                if (i == n && j == m)
                    dp_dst[i][j] = grid[i][j];
                else
                    dp_dst[i][j] = max(dp_dst[i + 1][j], dp_dst[i][j + 1]) + grid[i][j];
            }

        // prefix maxima of val[i][j] = dpS[i][j] + dpT[i][j] - grid[i][j]
        for (ll i = 1; i <= n; i++)
            for (ll j = 1; j <= m; j++) {
                ll val = dp_src[i][j] + dp_dst[i][j] - grid[i][j];
                row_pre[i][j] = max(row_pre[i][j - 1], val);
                col_pre[i][j] = max(col_pre[i - 1][j], val);
            }

        vector<pll> path;
        ll cx = n, cy = m;
        while (cx != 1 || cy != 1) {
            path.pb({cx, cy});
            pll p = prv[cx][cy];
            cx = p.f;
            cy = p.s;
        }
        path.pb({1, 1});
        flip(path);

        ll ans = 2e18;
        for (auto& [r, c] : path) {
            ll opt1 = mx - 2 * grid[r][c], bypass = NEG;
            // below-left: best path through (r+1, q) for q < c
            if (r < n && c > 1)
                bypass = max(bypass, row_pre[r + 1][c - 1]);
            // above-right: best path through (p, c+1) for p < r
            if (r > 1 && c < m)
                bypass = max(bypass, col_pre[r - 1][c + 1]);
            ans = min(ans, max(opt1, bypass));
        }

        cout << ans << '\n';
    }

    return 0;
}
