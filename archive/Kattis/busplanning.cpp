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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, k, c;
    cin >> n >> k >> c;
    vector<str> inv(n);
    map<str, ll> mp;
    FOR (i, n) {
        cin >> inv[i];
        mp[inv[i]] = i;
    }
    vector<ll> adj(n, (1 << n) - 1);
    FOR (i, k) {
        str s0, s1;
        cin >> s0 >> s1;
        ll x = mp[s0], y = mp[s1];
        adj[x] ^= (1 << y);
        adj[y] ^= (1 << x);
    }
    vector<bool> ok(1 << n, true);
    FOR (i, 1 << n) {
        if (__builtin_popcount(i) > c) {
            ok[i] = false;
        } else {
            ll x = i;
            FOR (j, n) {
                if (i & (1 << j)) {
                    x &= adj[j];
                }
            }
            if (x != i) {
                ok[i] = false;
            }
        }
    }
    vector<pair<ll, ll>> dp(1 << n, {1e18, 0});
    dp[0] = {0, 0};
    FOR (i, 1 << n) {
        for (ll j = i; j > 0; j = (j - 1) & i) {
            if (ok[j]) {
                if (dp[i ^ j].first + 1 < dp[i].first) {
                    dp[i] = {dp[i ^ j].first + 1, j};
                }
            }
        }
    }
    vector<ll> rv_bit;
    ll x = (1 << n) - 1;
    while (x > 0) {
        rv_bit.pb(dp[x].second);
        x ^= dp[x].second;
    }
    vector<vector<str>> rv;
    FOR (i, sz(rv_bit)) {
        vector<str> cur;
        FOR (j, n) {
            if (rv_bit[i] & (1 << j)) {
                cur.pb(inv[j]);
            }
        }
        rv.pb(cur);
    }
    cout << sz(rv) << '\n';
    FOR (i, sz(rv)) {
        FOR (j, sz(rv[i])) {
            cout << rv[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}