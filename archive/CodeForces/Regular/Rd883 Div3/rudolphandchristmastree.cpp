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
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ld n, d, h;
        cin >> n >> d >> h;
        vector<ld> ys(n), hs(n, h);
        FOR (i, n) {
            cin >> ys[i];
        }
        FOR (i, n - 1) {
            hs[i] = min(ys[i + 1] - ys[i], h);
        }
        ld rv = 0;
        FORE (x, hs) {
            ld d2 = d * (h - x) / h;
            rv += (d + d2) * x / 2;
        }
        cout << fixed << setprecision(10) << rv << '\n';
    }

    return 0;
}