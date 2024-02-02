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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll r, c, x; cin >> r >> c >> x;
    vector<vector<ll>> grid(r, vector<ll>(c));
    FOR(i, r) FOR(j, c) cin >> grid[i][j];
    vector<str> pass(r, str(c, '.'));
    FOB (i, 1, r - 1) FOB (j, 1, c - 1) {
        if (grid[i - 1][j] != -1 &&
            grid[i + 1][j] != -1 &&
            grid[i][j - 1] != -1 &&
            grid[i][j + 1] != -1 &&
            grid[i][j] < grid[i - 1][j] && grid[i][j] < grid[i + 1][j] &&
            grid[i][j] > grid[i][j - 1] && grid[i][j] > grid[i][j + 1])
        { pass[i][j] = 'x'; }
    }
    vector<vector<ll>> dp0(r, vector<ll>(x + 1, 1e9));
    FOR (i, r) dp0[i][0] = 0;
    FOR (j, c) {
        vector<vector<ll>> dp1(r, vector<ll>(x + 1, 1e9));
        FOR (i, r) {
            if (grid[i][j] == -1) continue;
            ll cur = grid[i][j];
            bool add = pass[i][j] == 'x';
            FOR (l, x + 1 - add) {
                ll mn = 1e9;
                for (ll k = -1; k <= 1; k++) {
                    if (i + k >= 0 && i + k < r) mn = min(mn, dp0[i + k][l]);
                }
                ll nl = l + add;
                dp1[i][nl] = min(dp1[i][nl], mn + cur);
            }
        }
        dp0 = dp1;
    }
    ll mn = 1e9;
    FOR (i, r) mn = min(mn, dp0[i][x]);
    if (mn >= 1e9) cout << "impossible\n";
    else cout << mn << '\n';

    return 0;
}