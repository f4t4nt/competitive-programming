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

constexpr ll MAX_N = 1e6 + 1;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<ll> primes;
    bitset<MAX_N> is_prime;
    is_prime.set();
    is_prime[0] = is_prime[1] = false;
    FOB (i, 2LL, MAX_N) {
        if (is_prime[i]) {
            primes.pb(i);
            for (ll j = i * i; j < MAX_N; j += i) {
                is_prime[j] = false;
            }
        }
    }

    ll n, rv = 0;
    cin >> n;
    vector<ll> a(n), cnt(MAX_N);
    FORE (x, a) {
        cin >> x;
        vector<ll> prime_factors;
        FORE (p, primes) {
            if (p * p > x) {
                break;
            }
            if (x % p == 0) {
                prime_factors.pb(p);
                while (x % p == 0) {
                    x /= p;
                }
            }
        }
        if (x > 1) {
            prime_factors.pb(x);
        }
        ll m = sz(prime_factors);
        vector<ll> prod(1 << m, 1);
        FOB (i, 1, 1 << m) {
            FOR (j, m) {
                if (i & (1 << j)) {
                    prod[i] = prod[i ^ (1 << j)] * prime_factors[j];
                    break;
                }
            }
            ll sgn = __builtin_popcount(i) & 1 ? 1 : -1;
            rv += sgn * cnt[prod[i]];
            cnt[prod[i]]++;
        }
    }
    cout << n * (n - 1) / 2 - rv << '\n';

    return 0;
}