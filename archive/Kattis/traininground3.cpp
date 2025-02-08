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

constexpr ll MOD = 998244353;

struct Binom {
    ll n;
    vector<ll> fac, ifac;
    Binom(ll n) : n(n), fac(n + 1), ifac(n + 1) {
        fac[0] = 1;
        FOR (i, n) fac[i + 1] = fac[i] * (i + 1) % MOD;
        ifac[n] = poww(fac[n], MOD - 2);
        FORR (i, n) ifac[i] = ifac[i + 1] * (i + 1) % MOD;
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
    ll inv(ll a) {
        return poww(a, MOD - 2);
    }
    ll choose(ll n, ll k) {
        if (k < 0 || k > n) return 0;
        else return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, k, p; cin >> n >> k >> p;
    Binom b(n);
    ll ans = 1;
    FOR (i, k) {
        ll m = n - i * p;
        ans = ans * b.choose(m, p) % MOD;
    }
    ll denom = b.inv(b.choose(n, p));
    denom = b.poww(denom, k);
    ans = ans * denom % MOD;
    ans = (MOD + 1 - ans) % MOD;
    cout << ans << '\n';

    return 0;
}