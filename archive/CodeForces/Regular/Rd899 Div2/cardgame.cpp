#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
 
#pragma GCC target("popcnt,lzcnt")
 
#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
 
#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FORE(x, C) for(auto &x : C)
 
#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

// imma show YOU how great i am.

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    FOR (i, n) cin >> a[i];
    // {original, flipped}
    vector<vector<ll>> dp(2, vector<ll>(n + 1));
    dp[1][0] = -1e18;
    FOR (i, n) {
        if (i % 2 == 0) {
            // if we add when flipped, can't add to score
            dp[0][i + 1] = max({dp[0][i], dp[1][i], dp[0][i] + a[i]});
            // we can only add to score if original
            dp[1][i + 1] = max({dp[1][i], dp[0][i] + a[i], dp[1][i] + a[i]});
        } else {
            // we can only add to score if flipped
            // OR we remove preemptively then use prev
            dp[0][i + 1] = max({dp[0][i], dp[1][i] + a[i], dp[1][i]});
            // if we add when original, can't add to score
            dp[1][i + 1] = max({dp[1][i], dp[0][i], dp[1][i] + a[i]});
        }
    }
    cout << max(dp[0][n], dp[1][n]) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}