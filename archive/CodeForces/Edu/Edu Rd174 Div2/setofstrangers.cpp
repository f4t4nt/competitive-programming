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

ll dx[4] = {1, 0, -1, 0};
ll dy[4] = {0, 1, 0, -1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        vector<vector<ll>> a(n, vector<ll>(m));
        for (auto &ai : a) for (ll &aij : ai) cin >> aij;
        vector<vector<pll>> color_map(n * m);
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < m; j++) {
                color_map[a[i][j] - 1].pb({i, j});
            }
        }
        vector<ll> cnt(n * m);
        for (ll i = 0; i < n * m; i++) {
            auto &cells = color_map[i];
            if (sz(cells) == 0) continue;
            bool adj = false;
            for (auto &[i, j] : cells) {
                for (ll k = 0; k < 4; k++) {
                    ll ni = i + dx[k], nj = j + dy[k];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                        if (a[ni][nj] == a[i][j]) {
                            adj = true;
                            break;
                        }
                    }
                }
                if (adj) break;
            }
            cnt[i] = adj ? 2 : 1;
        }
        ll ans = 0, mx = 0;
        for (ll i = 0; i < n * m; i++) {
            ans += cnt[i];
            mx = max(mx, cnt[i]);
        }
        cout << ans - mx << '\n';
    }

    return 0;
}