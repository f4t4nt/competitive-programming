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
// #define f first
// #define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
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

map<pll, vector<tuple<ll, ll, ll>>> rects = {
    {
        {2, 3},
        {
            {0, 0, 0},
            {1, 2, 1}
        }
    },
    {
        {5, 9},
        {
            {0, 0, 0},
            {0, 0, 2},
            {1, 1, 4},
            {2, 3, 0},
            {2, 2, 1},
            {0, 2, 3},
            {1, 4, 2},
            {1, 4, 4},
            {2, 5, 0},
            {0, 5, 2},
            {1, 6, 4},
            {0, 6, 0},
            {1, 8, 1},
            {0, 7, 2},
            {1, 8, 4}
        }
    }
};

void insert_trominos(ll dx, ll dy, bool flip, vector<tuple<ll, ll, ll>> &ref, vector<tuple<ll, ll, ll>> &trominos) {
    for (auto [dir, x, y] : ref) {
        if (flip) {
            swap(x, y);
            if (dir == 2) dir = 3;
        }
        trominos.pb({dir, dx + x, dy + y});
    }
}

bool eval(ll dx, ll dy, ll n, ll m, vector<tuple<ll, ll, ll>> &trominos) {
    if (n == 0 || m == 0) return true;
    if (n < 0 || m < 0) return false;
    for (auto [k, v] : rects) {
        auto [w, h] = k;
        if (m % w == 0 && eval(dx + h, dy, n - h, m, trominos)) {
            for (ll j = dy; j < dy + m; j += w) {
                insert_trominos(dx, j, 0, v, trominos);
            }
            return true;
        } elif (m % h == 0 && eval(dx + w, dy, n - w, m, trominos)) {
            for (ll j = dy; j < dy + m; j += h) {
                insert_trominos(dx, j, 1, v, trominos);
            }
            return true;
        } elif (n % w == 0 && eval(dx, dy + h, n, m - h, trominos)) {
            for (ll i = dx; i < dx + n; i += w) {
                insert_trominos(i, dy, 1, v, trominos);
            }
            return true;
        } elif (n % h == 0 && eval(dx, dy + w, n, m - w, trominos)) {
            for (ll i = dx; i < dx + n; i += h) {
                insert_trominos(i, dy, 0, v, trominos);
            }
            return true;
        }
    }
    return false;
}

vector<str> gen_grid(ll n, ll m, vector<tuple<ll, ll, ll>> &trominos) {
    vector<str> grid(n, str(m, '.'));
    for (auto [dir, x, y] : trominos) {
        vector<bool> adj(26);
        for (ll i = max(0ll, x-2); i < min(n, x+4); i++) {
            for (ll j = max(0ll, y-2); j < min(m, y+4); j++) {
                if (grid[i][j] != '.') adj[grid[i][j] - 'A'] = 1;
            }
        }
        ch c = 'A';
        while (adj[c - 'A']) c++;
        if (x < 0 || y < 0 || x >= n || y >= m) continue;
        if (dir == 0 && x < n - 1 && y < m - 1) grid[x][y] = grid[x+1][y] = grid[x][y+1] = c;
        elif (dir == 1 && x > 0 && y > 0) grid[x][y] = grid[x-1][y] = grid[x][y-1] = c;
        elif (dir == 2 && x > 0 && y < m - 1) grid[x][y] = grid[x-1][y] = grid[x][y+1] = c;
        elif (dir == 3 && x < n - 1 && y > 0) grid[x][y] = grid[x+1][y] = grid[x][y-1] = c;
    }
    return grid;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        if ((n * m) % 3 != 0 || min(n, m) == 1) cout << "NO\n";
        else {
            vector<tuple<ll, ll, ll>> trominos;
            if (eval(0, 0, n, m, trominos)) {
                cout << "YES\n";
                auto grid = gen_grid(n, m, trominos);
                for (str s : grid) cout << s << '\n';
            } else cout << "NO\n";
        }
    }

    return 0;
}