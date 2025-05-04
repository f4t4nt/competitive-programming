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

    ll t; cin >> t;
    while (t--) {
        ll n, q; cin >> n >> q;
        str ss; cin >> ss;
        vector<ll> s(n);
        for (ll i = 0; i < n; i++) s[i] = ss[i] == '1';
        ll cnt0 = n - accumulate(all(s), 0LL),
            tmp = poww(2, n - 4 + MOD - 1);
        while (q--) {
            ll i; cin >> i; i--;
            cnt0 += 2 * s[i] - 1;
            s[i] ^= 1;
            ll ans = tmp * (n * (n + 1) % MOD - 4 * cnt0 * n % MOD + 4 * cnt0 * cnt0 % MOD - 2) % MOD;
            ans = (ans + MOD) % MOD;
            cout << ans << '\n';
        }
    }

    return 0;
}