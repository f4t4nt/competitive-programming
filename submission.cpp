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
// #define f first
// #define s second

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

const ll MOD = 1e9 + 7;

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

    ll inv2 = poww(2, MOD - 2), inv4 = poww(4, MOD - 2);
    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> a(n), p(n);
        FOR (i, n) cin >> a[i];
        FOR (i, n) cin >> p[i];
        vector<ll> ti_num(n);
        FOR (i, n) {
            ti_num[i] = (10000 - 2 * p[i] % MOD + MOD) % MOD;
            ti_num[i] = (ti_num[i] + MOD) % MOD;
        }
        ll ti_den = poww(10000, MOD - 2), B = 10;
        vector<vector<ll>> idxs_b(B);
        FOR (i, n) FOR (b, B) if ((a[i] >> b) & 1)
            idxs_b[b].push_back(i);
        vector<ll> ref0(B), ref1(B);
        FOR (b, B) {
            ll cnt = idxs_b[b].size();
            if (cnt == 0) {
                ref0[b] = 1;
                ref1[b] = 0;
                continue;
            }
            ll num = 1;
            FOR (j, cnt) {
                ll idx = idxs_b[b][j];
                num = num * ti_num[idx] % MOD;
            }
            ll ex = cnt * (MOD - 2) % (MOD - 1),
                den_inv = poww(10000, ex);
            ref0[b] = num * den_inv % MOD;
            ref1[b] = (1 - ref0[b] + MOD) * inv2 % MOD;
        }
        vector<ll> pow2(2 * B);
        pow2[0] = 1;
        FOR1 (i, 2 * B) pow2[i] = pow2[i - 1] * 2 % MOD;
        ll ans = 0;
        FOR (b, B) {
            ll term = pow2[2 * b] * ref1[b] % MOD;
            ans = (ans + term) % MOD;
        }
        FOR (b, B) {
            for (ll c = b + 1; c < B; ++c) {
                ll num = 1, cnt = 0;
                FOR (i, n) {
                    ll sb = (a[i] >> b) & 1;
                    ll sc = (a[i] >> c) & 1;
                    if ((sb + sc) % 2 == 1) {
                        num = num * ti_num[i] % MOD;
                        cnt++;
                    }
                }
                ll ex = cnt * (MOD - 2) % (MOD - 1),
                    den_inv = poww(10000, ex),
                    tmp0 = num * den_inv % MOD,
                    tmp1 = (1 - ref0[b] - ref0[c] + tmp0 + 2 * MOD) % MOD;
                tmp1 = tmp1 * inv4 % MOD;
                ll term = 2 * pow2[b + c] % MOD * tmp1 % MOD;
                ans = (ans + term) % MOD;
            }
        }
        cout << ans % MOD << '\n';
    }

    return 0;
}