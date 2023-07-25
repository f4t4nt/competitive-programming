#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
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

ll pow(ll p, ll e) {
    ll rv = 1;
    while (e > 0) {
        if (e % 2 == 1) {
            rv *= p;
        }
        p *= p;
        e /= 2;
    }
    return rv;
}

ll pow_sols(ll p0, ll e, vector<ll> &qr) {
    ll p = pow(p0, e), rv = 0;
    qr = vector<ll>(p);
    FOR (i, p) {
        qr[i * i % p]++;
    }
    FOR (i, p) {
        rv += qr[i] * qr[(i + 1) % p];
    }
    for (ll i = 0LL; i < p; i += p0) {
        rv += qr[(i * i + 1) % p];
    }
    rv *= p / p0 * (p0 - 1);
    if (e > 1) {
        rv += pow_sols(p0, e - 2, qr) * p0 * p0 * p0;
    } else {
        rv++;
    }
    return rv;
}

ll zero(ll n, vector<ll> &qr) {
    ll rv = 1 + 3 * qr[0];
    FOR (i, n) {
        rv += qr[i] * (2 * qr[i] + qr[(n - i) % n]);
    }
    return rv;
}

ll diag(ll n, vector<ll> &qr) {
    ll rv = 0;
    FOB (i, 1LL, n) {
        rv += qr[2 * i * i % n];
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, rv = 1;
    vector<ll> qr;
    cin >> n;
    ll n0 = n;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            ll e = 0;
            while (n % p == 0) {
                n /= p;
                e++;
            }
            rv *= pow_sols(p, e, qr);
        }
    }
    if (n != 1) {
        rv *= pow_sols(n, 1, qr);
    }
    qr = vector<ll>(n0);
    FOB (i, 1LL, n0) {
        qr[i * i % n0]++;
    }
    rv -= zero(n0, qr);
    rv += diag(n0, qr);
    rv /= 2;
    cout << rv << '\n';

    return 0;
}