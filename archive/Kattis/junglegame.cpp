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

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    vector<pll> avoid(n);
    // vector<bitset<10001>> ref(10001);
    // for (auto &x : ref) x.set();
    vector<vector<bool>> ref(n + 1, vector<bool>(n + 1, 1));
    for (auto &e : avoid) {
        cin >> e.f >> e.s;
        if (e.f % 2 == 0 && e.s % 2 == 0) {
            ref[e.f / 2][e.s / 2] = 0;
        }
    }
    vector<pll> res;
    for (ll sum = 2 * n; sum >= 2; sum--) {
        for (ll x = 1; x <= n; x++) {
            ll y = sum - x;
            if (y > n || y < 1) continue;
            if (ref[x][y]) {
                res.pb({x, y});
                if (sz(res) == n) break;
                for (auto &e : avoid) {
                    ll nx = e.f - x, ny = e.s - y;
                    if (nx < 1 || ny < 1) continue;
                    if (nx > n || ny > n) continue;
                    ref[nx][ny] = 0;
                }
            }
        }
        if (sz(res) == n) break;
    }
    if (sz(res) == n) {
        cout << "YES\n";
        for (auto &e : res) cout << e.f << ' ' << e.s << '\n';
    } else {
        cout << "NO\n";
    }

    return 0;
}