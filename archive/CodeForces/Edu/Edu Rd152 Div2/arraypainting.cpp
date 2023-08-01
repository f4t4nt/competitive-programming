#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<ll> a(n);
    FORE (x, a) {
        cin >> x;
    }
    // {-1, 0, 1}
    // need 1 from next, don't need but no xtra, have 1 extra
    vector<vector<ll>> dp(n + 1, vector<ll>(3, 1e18));
    dp[0][1] = 0;
    FOR (i, n) {
        if (a[i] == 0) {
            // need one from next, didn't use coin nor get one from prev
            dp[i + 1][0] = dp[i][1];
            // equilibrium, got one by coin or took one from prev
            dp[i + 1][1] = min(dp[i][1] + 1, dp[i][2]); 
        } elif (a[i] == 1) {
            // need one from next, didn't use coin nor get one from prev OR counting on getting from next and giving to prev
            dp[i + 1][0] = min(dp[i][1], dp[i][0]);
            // equilibrium, got one by coin (and maybe gave to prev) or took one from prev
            dp[i + 1][1] = min({dp[i][1] + 1, dp[i][2], dp[i][0] + 1});
            // can give one, didn't give one to prev
            dp[i + 1][2] = min(dp[i][1] + 1, dp[i][2]);
        } elif (a[i] == 2) {
            // need one from next, didn't use coin nor get one from prev OR counting on getting from next and giving to prev
            dp[i + 1][0] = min(dp[i][1], dp[i][0]);
            // equilibrium, got one by coin (and maybe gave to prev) or took one from prev
            dp[i + 1][1] = min({dp[i][1] + 1, dp[i][2], dp[i][0] + 1});
            // can give one, got one by coin (maybe gave to prev, but still has spare), or took one from prev
            dp[i + 1][2] = min({dp[i][1] + 1, dp[i][2], dp[i][0] + 1});
        } else {
            assert(false);
        }
    }
    cout << min(dp[n][1], dp[n][2]) << '\n';

    return 0;
}