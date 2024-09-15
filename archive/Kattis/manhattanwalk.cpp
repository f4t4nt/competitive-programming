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

    ll r, c; ld p;
    cin >> r >> c >> p;
    vector<vector<ld>> dp(r, vector<ld>(c));
    FOB (sum, 1, r + c) {
        FOR (i, r) {
            ll j = sum - i;
            if (j < 0 || j >= c) continue;
            if (i == 0) {
                dp[i][j] = p / 4 + dp[i][j - 1];
            } elif (j == 0) {
                dp[i][j] = p / 4 + dp[i - 1][j];
            } else {
                ld x = dp[i][j - 1], y = dp[i - 1][j];
                if (x > y) swap(x, y);
                if (x + p <= y) {
                    dp[i][j] = x + p / 2;
                } else {
                    dp[i][j] = (((x + (y - x) / 2) * (y - x) / p + y * (p - y + x) / p) + x) / 2;
                }
            }
        }
    }
    cout << fixed << setprecision(10) << dp[r - 1][c - 1] << '\n';

    return 0;
}