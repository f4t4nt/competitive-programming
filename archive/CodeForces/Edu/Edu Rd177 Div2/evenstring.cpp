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

const ll MOD = 998244353;

ll poww(ll a, ll b) {
    ll rv = 1;
    while (b) {
        if (b & 1) rv = rv * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    vector<ll> fact(500001), invfact(500001);
    fact[0] = 1;
    for (ll i = 1; i <= 500001; i++) fact[i] = (fact[i - 1] * i) % MOD;
    invfact[500001] = poww(fact[500001], MOD - 1);
    for (ll i = 500001; i > 0; i--) invfact[i - 1] = (invfact[i] * i) % MOD;

    ll t; cin >> t;
    while (t--) {
        vector<ll> c(26);
        ll n = 0;
        for (ll i = 0; i < 26; i++) {
            cin >> c[i];
            n += c[i];
        }
        ll x = (n + 1) / 2, y = n / 2;
        vector<ll> pos, dp(x + 1);
        dp[0] = 1;
        for (ll i = 0; i < 26; i++) if (c[i] > 0) pos.pb(c[i]);
        for (ll cnt : pos)
            for (ll s = x; s >= cnt; s--)
                dp[s] = (dp[s] + dp[s - cnt]) % MOD;
        ll cnt = dp[x];
        if (cnt == 0) {
            cout << 0 << '\n';
            continue;
        }
        ll factor = (fact[x] * fact[y]) % MOD, den = 1;
        for (ll cnt : pos) den = (den * fact[cnt]) % MOD;
        den = poww(den, MOD - 2);
        factor = (factor * den) % MOD;
        ll ans = (cnt * factor ) % MOD;
        cout << ans % MOD << '\n';
    }

    return 0;
}