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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

vector<ll> fibs = {1, 1};

void solve(ll n) {
    FOB (b, 1, 1e6) {
        ll min_a = 1e9;
        FOR (k, sz(fibs)) {
            // fibs[k] * a + fibs[k + 1] * b == n
            // a = (n - fibs[k + 1] * b) / fibs[k]
            ll num = n - fibs[k + 1] * b, den = fibs[k];
            if (num % den == 0 && num > 0) {
                ll a = num / den;
                if (b >= a) {
                    min_a = min(min_a, a);
                }
            }
        }
        if (min_a != 1e9) {
            cout << min_a << ' ' << b << '\n';
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (fibs.back() < 1e9) {
        fibs.pb(fibs.back() + fibs[sz(fibs) - 2]);
    }

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        solve(n);
    }

    return 0;
}