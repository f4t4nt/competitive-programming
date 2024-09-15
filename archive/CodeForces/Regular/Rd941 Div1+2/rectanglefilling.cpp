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
        vector<str> grid(n);
        FOR (i, n) cin >> grid[i];
        bool ok[2] = {1, 1};
        {
            bool cur[4] = {0, 0, 0, 0};
            FOR (i, n) {
                cur[0] |= grid[i][0] == 'W';
                cur[1] |= grid[i][m - 1] == 'W';
                cur[2] |= grid[i][0] == 'B';
                cur[3] |= grid[i][m - 1] == 'B';
            }
            ok[0] = cur[0] && cur[1];
            ok[1] = cur[2] && cur[3];
        }
        {
            bool cur[4] = {0, 0, 0, 0};
            FOR (i, m) {
                cur[0] |= grid[0][i] == 'W';
                cur[1] |= grid[n - 1][i] == 'W';
                cur[2] |= grid[0][i] == 'B';
                cur[3] |= grid[n - 1][i] == 'B';
            }
            ok[0] &= cur[0] && cur[1];
            ok[1] &= cur[2] && cur[3];
        }
        if (ok[0] || ok[1]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}