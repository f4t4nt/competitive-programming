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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<ll> primes;
    vector<bool> is_prime(1e6 + 1, true);
    is_prime[0] = is_prime[1] = false;
    FOB (p, 2LL, 1e6 + 1) {
        if (is_prime[p]) {
            primes.pb(p);
            for (ll q = p * p; q <= 1e6; q += p) {
                is_prime[q] = false;
            }
        }
    }

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> cnts;
        FORE (p, primes) {
            if (p * p > n) {
                break;
            }
            ll e = 0;
            while (n % p == 0) {
                n /= p;
                e++;
            }
            if (e > 0) {
                cnts.pb(e);
            }
        }
        if (n > 1) {
            cnts.pb(1);
        }
        ll rv = 1;
        FORE (e, cnts) {
            rv *= e + 1;
        }
        cout << rv << '\n';
    }

    return 0;
}