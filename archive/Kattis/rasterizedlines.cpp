#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

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

constexpr ll P_MAX = 1e7;
bitset<P_MAX> prime_ref;
set<ll> primes;

set<ll> get_divs(vector<ll> primes) {
    set<ll> rv0 = {1};
    FORE (p, primes) {
        set<ll> rv1 = rv0;
        FORE (x, rv0) {
            rv1.insert(x * p);
        }
        rv0 = rv1;
    }
    return rv0;
}

vector<ll> get_primes(ll n) {
    vector<ll> rv;
    FORE (p, primes) {
        while (n % p == 0) {
            n /= p;
            rv.pb(p);
        }
        if (n == 1 || p * p > n) {
            break;
        }
    }
    if (n > 1) {
        rv.pb(n);
    }
    return rv;
}

ll phi(ll x) {
    vector<ll> p_vec = get_primes(x);
    set<ll> p_set;
    FORE (p, p_vec) {
        p_set.insert(p);
    }
    FORE (p, p_set) {
        x /= p;
        x *= p - 1;
    }
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll p = 2;
    while (p < P_MAX) {
        if (!prime_ref[p]) {
            primes.insert(p);
            for (ll x = p * 2; x < P_MAX; x += p) {
                prime_ref[x] = true;
            }
        }
        p++;
    }

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        if (n == 1) {
            cout << 1 << '\n';
            continue;
        }
        set<ll> divs0 = get_divs(get_primes(n)), divs1;
        FORE (d, divs0) {
            divs1.insert(d + 1);
        }
        ll rv = 0;
        FORE (x, divs1) {
            rv += phi(x);
        }
        cout << rv << '\n';
    }

    return 0;
}