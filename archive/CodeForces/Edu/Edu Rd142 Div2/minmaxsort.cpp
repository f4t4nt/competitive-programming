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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;

    while (t--) {
        ll n, rv = 0;
        cin >> n;
        vector<ll> p(n);
        FOR (i, n) {
            cin >> p[i];
        }
        if (n % 2 == 0) {
            ll lo = 0, hi = 0, lo_val = n / 2, hi_val = n / 2 + 1;
            while (lo < n && p[lo] != lo_val) {
                lo++;
            }
            while (hi < n && p[hi] != hi_val) {
                hi++;
            }
            if (lo < hi && hi < n && p[lo] == lo_val && p[hi] == hi_val) {
                rv = 2;
                while (lo >= 0 && hi < n) {
                    lo_val--;
                    hi_val++;
                    while (lo >= 0 && p[lo] != lo_val) {
                        lo--;
                    }
                    while (hi < n && p[hi] != hi_val) {
                        hi++;
                    }
                    if (lo >= 0 && hi < n && p[lo] == lo_val && p[hi] == hi_val) {
                        rv += 2;
                    } else {
                        break;
                    }
                }
            }
        } else {
            ll lo = 0, hi = 0, lo_val = (n + 1) / 2, hi_val = (n + 1) / 2;
            while (lo < n && p[lo] != lo_val) {
                lo++;
            }
            hi = lo;
            rv = 1;
            while (lo >= 0 && hi < n) {
                lo_val--;
                hi_val++;
                while (lo >= 0 && p[lo] != lo_val) {
                    lo--;
                }
                while (hi < n && p[hi] != hi_val) {
                    hi++;
                }
                if (lo >= 0 && hi < n && p[lo] == lo_val && p[hi] == hi_val) {
                    rv += 2;
                } else {
                    break;
                }
            }
        }
        rv = (n - rv) / 2;
        cout << rv << '\n';
    }

    return 0;
}