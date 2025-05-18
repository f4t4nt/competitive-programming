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

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

ll kx[] = {1, 2, 2, 1, -1, -2, -2, -1};
ll ky[] = {2, 1, -1, -2, -2, -1, 1, 2};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    vector<vector<ll>> ans(n, vector<ll>(n, 1e18));
    queue<pll> q;
    q.push({0, 0});
    ans[0][0] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (ll i = 0; i < 8; i++) {
            ll nx = x + kx[i];
            ll ny = y + ky[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (ans[nx][ny] > ans[x][y] + 1) {
                ans[nx][ny] = ans[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    for (auto &v : ans) {
        for (ll x : v) cout << x << ' ';
        cout << '\n';
    }

    return 0;
}
