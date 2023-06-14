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

bool intersect(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3, ll x4, ll y4) {
    ll a1 = y2 - y1, b1 = x1 - x2, c1 = a1 * x1 + b1 * y1;
    ll a2 = y4 - y3, b2 = x3 - x4, c2 = a2 * x3 + b2 * y3;
    ll det = a1 * b2 - a2 * b1;
    if (det == 0) {
        if (a1 * x3 + b1 * y3 == c1) {
            if (min(x1, x2) <= x3 && x3 <= max(x1, x2) && min(y1, y2) <= y3 && y3 <= max(y1, y2)) {
                return true;
            }
            if (min(x1, x2) <= x4 && x4 <= max(x1, x2) && min(y1, y2) <= y4 && y4 <= max(y1, y2)) {
                return true;
            }
            if (min(x3, x4) <= x1 && x1 <= max(x3, x4) && min(y3, y4) <= y1 && y1 <= max(y3, y4)) {
                return true;
            }
            if (min(x3, x4) <= x2 && x2 <= max(x3, x4) && min(y3, y4) <= y2 && y2 <= max(y3, y4)) {
                return true;
            }
        }
        return false;
    } else {
        ld x = (ld) (b2 * c1 - b1 * c2) / det;
        ld y = (ld) (a1 * c2 - a2 * c1) / det;
        if (min(x1, x2) <= x && x <= max(x1, x2) && min(y1, y2) <= y && y <= max(y1, y2)) {
            if (min(x3, x4) <= x && x <= max(x3, x4) && min(y3, y4) <= y && y <= max(y3, y4)) {
                return true;
            }
        }
        return false;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        cout << (intersect(x1, y1, x2, y2, x3, y3, x4, y4) ? "YES" : "NO") << '\n';
    }

    return 0;
}