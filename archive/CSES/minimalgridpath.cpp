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

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
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

    ll n; cin >> n;
    vector<str> grid(n);
    for (str &s : grid) cin >> s;
    str res;
    pair<ch, vector<pll>> cur, nxt;
    cur = {grid[0][0], {{0, 0}}};
    for (ll sum = 1; sum <= 2 * n - 1; sum++) {
        res += cur.f;
        nxt = {'Z' + 1, {}};
        vector<bool> vis(n);
        for (auto [x, y] : cur.s) {
            if (x + 1 < n && !vis[x + 1]) {
                if (nxt.f > grid[x + 1][y]) {
                    vis[x + 1] = true;
                    nxt.f = grid[x + 1][y];
                    nxt.s = {{x + 1, y}};
                } elif (nxt.f == grid[x + 1][y]) {
                    vis[x + 1] = true;
                    nxt.s.pb({x + 1, y});
                }
            }
            if (y + 1 < n && !vis[x]) {
                if (nxt.f > grid[x][y + 1]) {
                    vis[x] = true;
                    nxt.f = grid[x][y + 1];
                    nxt.s = {{x, y + 1}};
                } elif (nxt.f == grid[x][y + 1]) {
                    vis[x] = true;
                    nxt.s.pb({x, y + 1});
                }
            }
        }
        cur = nxt;
    }
    cout << res << '\n';

    return 0;
}
