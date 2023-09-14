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

constexpr ll MOD = 1e9 + 7;
constexpr ll MAXN = 1e6 + 1;

struct Binom {
    ll n;
    vector<ll> fac, ifac;
    Binom(ll n) : n(n) {
        fac.resize(n + 1);
        ifac.resize(n + 1);
        fac[0] = 1;
        FOB (i, 1, n + 1) {
            fac[i] = fac[i - 1] * i % MOD;
        }
        ifac[n] = pow(fac[n], MOD - 2);
        FORR (i, n) {
            ifac[i] = ifac[i + 1] * (i + 1) % MOD;
        }
    }
    ll pow(ll a, ll b) {
        ll rv = 1;
        while (b) {
            if (b & 1) {
                rv = rv * a % MOD;
            }
            a = a * a % MOD;
            b >>= 1;
        }
        return rv;
    }
    ll choose(ll n, ll k) {
        if (k < 0 || k > n) {
            return 0;
        }
        return fac[n] * ifac[k] % MOD * ifac[n - k] % MOD;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, k;
    cin >> n >> k;
    Binom binom(k);
    ll rv = 0, c = 1;
    FOR (i, k + 1) {
        rv = ((rv + c * binom.choose(k, i) % MOD
            * binom.pow(k - i, n) % MOD) % MOD + MOD) % MOD;
        c = -c;
    }
    cout << rv << '\n';

    return 0;
}