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

ll pow(ll x, ll p, ll MOD) {
    ll rv = 1, base = x;
    while (p) {
        if (p & 1) rv = (rv * base) % MOD;
        base = (base * base) % MOD;
        p >>= 1;
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<ll> pow2 = {1}, pow5={1};
    do {
        pow2.pb(pow2.back() * 2);
    } while (pow2.back() < 1e9);
    do {
        pow5.pb(pow5.back() * 5);
    } while (pow5.back() < 1e9);
    set<ll> s;
    FORE (x, pow2) {
        FORE (y, pow5) {
            if (x * y <= 1e9) {
                s.insert(x * y + 1);
            }
        }
    }
    ll n;
    cin >> n;
    vector<ll> a(n), next10(n, 1);
    FOR (i, n) {
        cin >> a[i];
        while (next10[i] <= a[i]) {
            next10[i] *= 10;
        }
    }
    FORE (p, s) {
        bool ok = true;
        FOR (i, n) {
            if (pow(a[i], p, next10[i]) != a[i]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << p << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';

    return 0;
}