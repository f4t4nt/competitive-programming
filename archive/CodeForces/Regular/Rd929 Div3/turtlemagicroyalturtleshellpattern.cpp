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

ll cnt = 0;
const ll MOD = 998244353;

bool ok(ll n, ll m, vector<vector<ll>> &grid) {
    FOB (i, 1, n - 1) {
        FOB (j, 1, m - 1) {
            if (grid[i][j] == -1) continue;
            if (grid[i][j] == grid[i - 1][j - 1] && grid[i][j] == grid[i + 1][j + 1]) {
                return false;
            }
            if (grid[i][j] == grid[i - 1][j + 1] && grid[i][j] == grid[i + 1][j - 1]) {
                return false;
            }
        }
    }
    FOR (i, n) {
        FOR (j, m - 2) {
            if (grid[i][j] == -1) continue;
            if (grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2]) {
                return false;
            }
        }
    }
    FOR (j, m) {
        FOR (i, n - 2) {
            if (grid[i][j] == -1) continue;
            if (grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j]) {
                return false;
            }
        }
    }
    return true;
}

void print_grid(ll n, ll m, vector<vector<ll>> &grid) {
    // FOR (i, n) {
    //     FOR (j, m) cout << grid[i][j];
    //     cout << endl;
    // }
    // cout << endl;
    cnt++;
}

void brute(ll i, ll j, ll n, ll m, vector<vector<ll>> &grid) {
    if (j >= m) i++, j = 0;
    if (i >= n) {
        if (ok(n, m, grid)) print_grid(n, m, grid);
        return;
    }
    grid[i][j] = 0;
    if (ok(n, m, grid)) brute(i, j + 1, n, m, grid);
    grid[i][j] = 1;
    if (ok(n, m, grid)) brute(i, j + 1, n, m, grid);
    grid[i][j] = -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    // // ll n = 5, m = 5;
    // FOB (n, 5, 10) FOB (m, 5, 10) {
    //     cnt = 0;
    //     vector<vector<ll>> grid(n, vector<ll>(m, -1));
    //     brute(0, 0, n, m, grid);
    //     cout << cnt << endl;
    // }

    ll t; cin >> t;
    while (t--) {
        ll n, m, q; cin >> n >> m >> q;
        bitset<8> ok;
        ok.set();
        cout << 8 << '\n';
        while (q--) {
            ll x, y; cin >> x >> y;
            str shape; cin >> shape;
            ll b = shape == "square";
            FOR (i, 8) if (ok[i]) {
                ll offset = i % 4, exp;
                if (i < 4) { // horizontal
                    if (y % 2 == 0) offset += 2;
                    exp = ((x + offset) / 2) % 2;
                } else { // vertical
                    if (x % 2 == 0) offset += 2;
                    exp = ((y + offset) / 2) % 2;
                }
                if (exp != b) ok[i] = 0;
            }
            cout << ok.count() << '\n';
        }
    }

    return 0;
}