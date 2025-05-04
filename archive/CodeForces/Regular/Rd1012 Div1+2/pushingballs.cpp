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
        for (str &row : grid) cin >> row;
        bool ok = true;
        for (ll i = 0; i < n && ok; i++) {
            for (ll j = 0; j < m && ok; j++) {
                bool row_ok = true, col_ok = true;
                if (grid[i][j] == '1') {
                    for (ll x = i; x >= 0 && row_ok; x--) {
                        row_ok = (grid[x][j] == '1');
                    }
                    if (!row_ok) {
                        for (ll y = j; y >= 0 && col_ok; y--) {
                            col_ok = (grid[i][y] == '1');
                        }
                        if (!col_ok) {
                            ok = false;
                            break;
                        }
                    }
                }
            }
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}