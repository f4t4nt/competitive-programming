#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <string.h>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

constexpr ll MOD = 998244353;

vector<ll> get_prime_factors(ll n) {
    vector<ll> factors;
    if (n % 2 == 0) {
        factors.pb(2);
        while (n % 2 == 0) {
            n /= 2;
        }
    }
    FOBI (i, 3, sqrt(n) + 1, 2) {
        if (n % i == 0) {
            factors.pb(i);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        factors.pb(n);
    }
    return factors;
}

ll phi(ll n, vector<ll> factors) {
    ll rv = n;
    FORE(f, factors) {
        rv -= rv / f;
    }
    return rv;
}

ll bitcount(ll n) {
    ll rv = 0;
    while (n) {
        rv += n & 1;
        n >>= 1;
    }
    return rv;
}

ll coprime_cnt(ll n, ll m) {
    vector<ll> factors = get_prime_factors(n);
    ll cnt = m / n, max_multiple = cnt * n, rv = phi(n, factors) * cnt;
    if (max_multiple == m) {
        return rv;
    }
    FOR (i, 1 << sz(factors)) {
        ll multiple = 1, sign = bitcount(i) % 2 ? -1 : 1;
        FOR (j, sz(factors)) {
            if (i & (1 << j)) {
                multiple *= factors[j];
            }
        }
        rv += sign * (m / multiple - max_multiple / multiple);
    }
    return rv;
}

int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll n, m;
        cin >> n >> m;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
        }
        bool valid = true;
        vector<ll> ref(n);
        FOR (i, n - 1) {
            if (a[i] % a[i + 1] != 0) {
                valid = false;
                break;
            }
            ref[i + 1] = a[i] / a[i + 1];
        }
        if (!valid) {
            cout << "0\n";
            continue;
        }
        ll rv = 1;
        vector<ll> cnt(n);
        FOB (i, 1, n) {
            cnt[i] = coprime_cnt(ref[i], m / a[i]);
            rv = (rv * cnt[i]) % MOD;
        }
        cout << rv << '\n';
    }
    return 0;
}