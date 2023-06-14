#include <bits/stdc++.h>

using namespace std;

using ll = long long;
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

ll cnt_factors(ll x) {
    ll rv = 0;
    for (ll i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            rv++;
            if (i * i != x) {
                rv++;
            }
        }
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll x;
    cin >> x;
    if (x == 1) {
        cout << 1 << '\n';
        return 0;
    }
    for (ll p = 60; p >= 2; p--) {
        ld nd = pow(x, (ld) 1 / p);
        ll n = (ll) round(nd);
        if (abs(nd - n) < 1e-6) {
            ll xn = 1, pn = p;
            while (pn--) {
                xn *= n;
            }
            if (x == xn && cnt_factors(n) == p) {
                cout << n << '\n';
                return 0;
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}