#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef string str;
typedef char ch;
typedef long double ld;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define fliip(C) reverse(all(C))
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

const ll MOD = 1e9 + 7;

ll mod_pow(ll a, ll b) {
    ll rv = 1;
    while (b) {
        if (b & 1) rv = rv * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return rv;
}

int main() {
    ll t; cin >> t;

    vector<ll> fact(2 * 1e6 + 1, 1), ifact(2 * 1e6 + 1, 1);
    for (ll i = 1; i <= 2 * 1e6; i++) fact[i] = fact[i - 1] * i % MOD;
    ifact[2 * 1e6] = mod_pow(fact[2 * 1e6], MOD - 2);
    for (ll i = 2 * 1e6 - 1; i > 0; i--) ifact[i] = ifact[i + 1] * (i + 1) % MOD;

    while (t--) {
        ll n, m; cin >> n >> m;
        n--; m--;
        ll rv = (fact[n + m] * ifact[n]) % MOD * ifact[m] % MOD;
        if (n != 0) rv *= 2;
        if (m != 0) rv *= 2;
        cout << rv % MOD << "\n";
    }
}