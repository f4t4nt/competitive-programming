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

#pragma GCC target("popcnt")

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
        ll res = 1;
        while (b) {
            if (b & 1) {
                res = res * a % MOD;
            }
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
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

    ll n;
    cin >> n;
    Binom binom(n);
    ll rv = 0, sgn = 1;
    FOR (i, n + 1) {
        rv += sgn * binom.choose(n, i) % MOD * binom.fac[n - i] % MOD;
        rv = (rv % MOD + MOD) % MOD;
        sgn *= -1;
    }
    cout << rv << '\n';

    return 0;
}