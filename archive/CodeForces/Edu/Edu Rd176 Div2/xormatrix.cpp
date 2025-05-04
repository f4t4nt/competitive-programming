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
const ll K = 32;
ll dp[K][2][2][2];

ll mul(ll a, ll b) {
    return a * b % MOD;
}

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
        ll n, m, A, B; cin >> n >> m >> A >> B;
        memset(dp, 0, sizeof(dp));
        dp[0][0][0][0] = 1;
        for (ll i = 0; i < K - 1; i++) {
            for (ll fa : {0, 1}) {
                for (ll fb : {0, 1}) {
                    for (ll fx : {0, 1}) {
                        ll j = K - 2 - i,
                            d = dp[i][fa][fb][fx],
                            ca = (A >> j) & 1,
                            cb = (B >> j ) & 1;
                        for (ll a : {0, 1}) {
                            for (ll b : {0, 1}) {
                                for (ll x : {0, 1}) {
                                    if (fa == 0 && ca == 0 && a == 1) continue;
                                    if (fb == 0 && cb == 0 && b == 1) continue;
                                    if (fx == 0 && a == 0 && x == 1) continue;
                                    if (fx == 0 && b == 0 && x == 1) continue;
                                    ll nfa = fa || (ca == 1 && a == 0),
                                        nfb = fb || (cb == 1 && b == 0),
                                        nfx = fx || x == 1;
                                    dp[i + 1][nfa][nfb][nfx] += d;
                                    dp[i + 1][nfa][nfb][nfx] %= MOD;
                                }
                            }
                        }
                    }
                }
            }
        }
        ll case11 = mul(A + 1, B + 1),
            case12 = mul(mul(mul(A, A + 1), B + 1), poww(2, n - 1) - 1),
            case21 = mul(mul(mul(B, B + 1), A + 1), poww(2, m - 1) - 1),
            case22 = mul(mul(poww(2, n) - 2, poww(2, m) - 2),
                        dp[K - 1][0][0][1] + dp[K - 1][0][1][1] + 
                        dp[K - 1][1][0][1] + dp[K - 1][1][1][1]),
            ans = (case11 + case12 + case21 + case22) % MOD;
        cout << ans << '\n';
    }

    return 0;
}