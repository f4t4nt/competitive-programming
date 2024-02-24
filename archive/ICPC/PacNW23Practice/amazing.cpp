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
#define x first
#define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

set<pll> vis;
set<pair<pll, pll>> walls;
str dir[4] = {"up", "down", "left", "right"};
ll dx[4] = {0, 0, -1, 1};
ll dy[4] = {-1, 1, 0, 0};

bool dfs(pll cur, pll prv) {
    vis.insert(cur);
    FOR(i, 4) {
        pll nxt = {cur.x + dx[i], cur.y + dy[i]};
        if (vis.count(nxt) || walls.count({cur, nxt})) continue;
        cout << dir[i] << endl;
        str s; cin >> s;
        if (s == "ok") {
            if (dfs(nxt, cur)) return 1;
            else cout << dir[i ^ 1] << endl, cin >> s;
        } elif (s == "wall") {
            walls.insert({cur, nxt});
            walls.insert({nxt, cur});
        } elif (s == "solved") {
            return 1;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    if (!dfs({0, 0}, {0, 0})) cout << "no way out" << endl;

    return 0;
}