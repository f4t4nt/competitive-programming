#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define ins insert
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

ll pow2(ll x, ll &MOD) {
    ll rv = 1, base = 2;
    while (x > 0) {
        if (x & 1) {
            rv = (rv * base) % MOD;
        }
        base = (base * base) % MOD;
        x >>= 1;
    }
    return rv;
}

ll gcd(ll a, ll b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, MOD;
    cin >> n >> MOD;

    ll rv = 0, ref = 0;
    FOB (i, 2, n) {
        ll g = gcd(i, n);
        if (g > 1) {
            ref++;
            rv = (rv + pow2(g - 1, MOD)) % MOD;
        }
    }
    rv = (rv - ref + MOD) % MOD;
    rv = ((n - 2) * rv) % MOD;
    cout << rv << '\n';

    return 0;
}