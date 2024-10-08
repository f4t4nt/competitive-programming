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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> q;
    vector<ld> h(n + 1);
    FOR (i, n + 1) {
        cin >> h[i];
    }

    while (q--) {
        ld g;
        cin >> g;
        g *= 10;
        auto f = [&](ll i) {
            return (ld) h[i] - g * i;
        };
        vector<ll> idxs(n + 1);
        iota(all(idxs), 0);
        sort(all(idxs), [&](ll i, ll j) {
            return f(i) < f(j) || (f(i) == f(j) && i < j);
        });
        ld rv = -1;
        ll lo = n;
        FORE (hi, idxs) {
            if (lo < hi) {
                ld xtra = 0;
                if (lo > 0) {
                    xtra = max(xtra, (f(hi) - f(lo)) / (f(lo - 1) - f(lo)));
                }
                if (hi < n) {
                    xtra = max(xtra, (f(hi) - f(lo)) / (f(hi) - f(hi + 1)));
                }
                xtra = min(xtra, 1.0L);
                rv = max(rv, xtra + hi - lo);
            }
            lo = min(lo, hi);
        }
        if (rv < 1e-1) {
            cout << "impossible\n";
        } else {
            cout << fixed << setprecision(10) << rv << '\n';
        }
    }

    return 0;
}