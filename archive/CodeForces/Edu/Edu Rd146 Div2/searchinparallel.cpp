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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n, s1, s2;
        cin >> n >> s1 >> s2;
        set<pair<ll, ll>> r;
        FOR (i, n) {
            ll x;
            cin >> x;
            r.insert({x, i + 1});
        }
        vector<ll> a, b;
        for (auto it = r.rbegin(); it != r.rend(); it++) {
            if ((sz(a) + 1) * s1 <= (sz(b) + 1) * s2) {
                a.pb(it->second);
            } else {
                b.pb(it->second);
            }
        }
        cout << sz(a) << ' ';
        FORE (x, a) {
            cout << x << ' ';
        }
        cout << '\n';
        cout << sz(b) << ' ';
        FORE (x, b) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}