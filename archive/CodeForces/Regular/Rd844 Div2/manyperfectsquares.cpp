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

ll fast_sqrt(ll n) {
    ll l = 0, r = 1e9;
    while (l < r) {
        ll m = (l + r) / 2;
        if (m * m < n) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while(t--) {
        ll n;
        cin >> n;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
        }

        ll rv = 1;
        set<ll> d2s;

        FOR (i, n) {
            FOR (j, i) {
                ll d = a[i] - a[j];
                vector<ll> factors;
                for (ll k = 1; k * k <= d; k++) {
                    if (d % k == 0) {
                        factors.pb(k);
                    }
                }
                FORE (f, factors) {
                    ll x = (f + d / f) / 2, y = (d / f - f) / 2;
                    if (x <= 0 || y <= 0 || (x + y) * (x - y) != d) {
                        continue;
                    }
                    ll d2 = x * x - a[i], tv = 0;
                    if (d2s.count(d2) || d2 < 0) {
                        continue;
                    }
                    d2s.insert(d2);
                    FOR (k, n) {
                        ll sqrta = fast_sqrt(a[k] + d2);
                        if (sqrta * sqrta == a[k] + d2) {
                            tv++;
                        }
                    }
                    rv = max(rv, tv);
                }
            }
        }
        
        cout << rv << '\n';
    }

    return 0;
}