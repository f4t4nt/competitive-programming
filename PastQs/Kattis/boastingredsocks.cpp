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

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    map<ll, ll> ref;

    FOB (m, 2LL, 5e4 + 1) {
        ref[m * (m - 1)] = m;
    }

    while (true) {
        ll p, q;
        cin >> p >> q;
        if (p == 0 && q == 0) {
            break;
        }
        if (p == 0) {
            cout << 0 << ' ' << 2 << '\n';
        } elif (p == q) {
            cout << 2 << ' ' << 0 << '\n';
        } else {
            ll g = gcd(p, q);
            p /= g;
            q /= g;
            ll rv = 0;
            FORE (x, ref) {
                ll m, v;
                tie(m, v) = x;
                ll tmp = p * m;
                if (tmp % q != 0) {
                    continue;
                }
                if (ref.count(tmp / q)) {
                    rv = tmp;
                    break;
                }
            }
            if (rv == 0) {
                cout << "impossible\n";
            } else {
                ll n = ref[rv / q], m = ref[rv / p];
                cout << n << ' ' << m - n << '\n';
            }
        }
    }

    return 0;
}