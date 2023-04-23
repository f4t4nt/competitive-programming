#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

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

ll pow(ll x, ll p) {
    ll rv = 1;
    while(p) {
        if(p & 1) rv = (rv * x) % MOD;
        x = (x * x) % MOD;
        p >>= 1;
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll m, k;
    cin >> m >> k;
    vector<ll> coeff(k + 1, 2);
    coeff[1] = 1;

    FOB (d, 2LL, k + 1) {
        if (abs(coeff[d]) == 2) {
            coeff[d] = -1;
            for (ll j = d * d; j <= k; j += d * d) {
                coeff[j] = 0;
            }
            for (ll j = 2 * d; j <= k; j += d) {
                if (coeff[j] == 2) {
                    coeff[j] = -1;
                } else {
                    coeff[j] = -coeff[j];
                }
            }
        }
    }

    ll rv = 1;
    FOB (j, 1, k + 1) {
        rv += (coeff[j] * (pow(2 * (k / j) + 1, m) + MOD - 1)) % MOD;
        rv %= MOD;
        if (rv < 0) {
            rv += MOD;
        }
    }

    cout << rv << "\n";
    
    return 0;
}
