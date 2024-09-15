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

    ll n; cin >> n;
    vector<pll> proj(n);
    FOR (i, n) cin >> proj[i].f >> proj[i].s;
    vector<ll> dp0(25e5 + 1, 1e18);
    dp0[0] = 0;
    FOR (i, n) {
        vector<ll> dp1(25e5 + 1, 1e18);
        FORR (j, 25e5 + 1) {
            dp1[j] = dp0[j] + proj[i].s;
            if (j + proj[i].f <= 25e5) dp1[j + proj[i].f] = min(dp1[j + proj[i].f], dp0[j]);
        }
        dp0 = dp1;
    }
    ll ans = 1e18;
    FOR (i, 25e5 + 1) ans = min(ans, max(i, dp0[i]));
    cout << ans << '\n';

    return 0;
}