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
// #define x first
// #define y second

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

const ll MAXQ = 1e5 + 5;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m; cin >> n >> m;
    vector<ll> d0(n);
    FOR (i, n) cin >> d0[i];
    set<ll> d(all(d0));
    vector<pair<ch, ll>> queries(m);
    FOR (i, m) {
        cin >> queries[i].first >> queries[i].second;
        if (queries[i].first == 'X') d.erase(queries[i].second);
    }
    vector<ll> dp(MAXQ, 1e9);
    dp[0] = 0;
    for (ll x : d) FOR (i, MAXQ - x) {
        dp[i + x] = min(dp[i + x], dp[i] + 1);
    }
    vector<ll> ans(m);
    for (ll i = m - 1; i >= 0; i--) {
        auto [c, x] = queries[i];
        if (c == 'X') {
            d.insert(x);
            FOR (j, MAXQ - x) {
                dp[j + x] = min(dp[j + x], dp[j] + 1);
            }
        } else {
            ans[i] = dp[x] == 1e9 ? -1 : dp[x];
        }
    }
    for (ll x : ans) if (x) cout << x << '\n';

    return 0;
}