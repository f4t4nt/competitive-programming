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

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    while (n--) {
        while (true) {
            ll x = rand() % 100, y = rand() % 100, d0, d1, da = -1, db = -1;
            cout << x << ' ' << y << endl;
            cin >> d0;
            cout << x + 1 << ' ' << y << endl;
            cin >> d1;
            // (cx - x)     * (cx - x)     + (cy - y) * (cy - y) = d0
            // (cx - x - 1) * (cx - x - 1) + (cy - y) * (cy - y) = d1
            // (cx - x - 1) * (cx - x - 1) - (cx - x) * (cx - x) = d1 - d0
            // -2 * cx + 2 * x + 1 = d1 - d1
            // -2 * cx = -2 * x + d1 - d0 - 1
            // cx = x + (d1 - d0 - 1) / -2
            // c = (d1 - d0 - 1) / -2
            // c * c + (cy - y) * (cy - y) = d0
            // cy - y = +- sqrt(d0 - c * c)
            // cy = y +- sqrt(d0 - c * c)
            ll c = d1 - d0 - 1;
            c /= -2;
            ll cx = x + c, cya = y + sqrt(d0 - c * c), cyb = y - sqrt(d0 - c * c);
            if (cx >= 0 && cx <= 1e6 && cya >= 0 && cya <= 1e6) {
                cout << cx << ' ' << cya << endl;
                cin >> da;
                if (da == 0) {
                    break;
                }
            }
            if (cx >= 0 && cx <= 1e6 && cyb >= 0 && cyb <= 1e6) {
                cout << cx << ' ' << cyb << endl;
                cin >> db;
                if (db == 0) {
                    break;
                }
            }
        }
    }

    return 0;
}