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
#define x first
#define y second

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

ld get_dist(ll u, ll v, vector<vector<ld>> &dist, vector<vector<ld>> &degs, ld &alpha) {
    ld d = dist[u][v], beta = degs[u][v];
    return d * (abs(sin(alpha - beta)) + abs(cos(alpha - beta)));
}

ld eval(ll n, vector<pld> &pts, vector<vector<ld>> &dist, vector<vector<ld>> &degs, ld &alpha) {
    vector<vector<ld>> dp(1 << n, vector<ld>(n, 1e18));
    FOR (i, n) dp[1 << i][i] = 0;
    FOR (x, 1 << n) {
        FOR (i, n) {
            if (!(x & (1 << i))) continue;
            ld cur = dp[x][i];
            FOR (j, n) {
                ll y = x | (1 << j);
                ld nxt = cur + get_dist(i, j, dist, degs, alpha);
                dp[y][j] = min(dp[y][j], nxt);
            }
        }
    }
    return *min_element(all(dp.back()));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    vector<pld> pts(n);
    for (pld &p : pts) cin >> p.x >> p.y;
    vector<vector<ld>> dist(n, vector<ld>(n)), degs = dist;
    FOR (i, n) for (ll j = i + 1; j < n; j++) {
        dist[i][j] = dist[j][i] = hypot(pts[i].x - pts[j].x, pts[i].y - pts[j].y);
        degs[i][j] = degs[j][i] = atan2(pts[j].y - pts[i].y, pts[j].x - pts[i].x);
    }

    ld ans = 1e18;
    FOR (i, n) for (ll j = i + 1; j < n; j++)
        ans = min(ans, eval(n, pts, dist, degs, degs[i][j]));
    cout << fixed << setprecision(10) << ans << '\n';

    return 0;
}