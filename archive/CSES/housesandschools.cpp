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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

// https://cses.fi/problemset/task/2087

// sum of a[i] * |i - x| for i in [l, r]
ll get_cost0(ll l, ll x, ll r, vector<ll> &c) {
    ll rv = 0;
    FOB (i, l, r + 1) {
        rv += c[i] * abs(i - x);
    }
    return rv;
}

ll get_cost1(ll l, ll x, ll r, ll &n, vector<ll> &pref, vector<ll> &pref_inc, vector<ll> &pref_dec) {
    // [l, x]
    ll rv0 = pref_dec[x + 1] - pref_dec[l];
    rv0 -= (n - x) * (pref[x + 1] - pref[l]);
    // [x, r]
    ll rv1 = pref_inc[r + 1] - pref_inc[x];
    rv1 -= (x + 1) * (pref[r + 1] - pref[x]);
    return rv0 + rv1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, k;
    cin >> n >> k;
    vector<ll> c(n), pref(n + 1), pref_inc(n + 1), pref_dec(n + 1);
    FOR (i, n) {
        cin >> c[i];
        pref[i + 1] = pref[i] + c[i];
        pref_inc[i + 1] = pref_inc[i] + c[i] * (i + 1);
        pref_dec[i + 1] = pref_dec[i] + c[i] * (n - i);
    }
    // FOR (l, n) {
    //     FOB (x, l, n) {
    //         FOB (r, x, n) {
    //             assert(get_cost0(l, x, r, c) == get_cost1(l, x, r, n, pref, pref_inc, pref_dec));
    //         }
    //     }
    // }
    // dp[i][j] = min cost of first i houses with j schools
    vector<vector<ll>> dp(n + 1, vector<ll>(k + 1, 1e18));
    

    return 0;
}