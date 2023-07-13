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

constexpr ld EPS = 1e-9;

ld tri_area(ld a, ld b, ld c) {
    ld s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ld a, b, c;
    cin >> a >> b >> c;
    if (a + b < c ||
        b + c < a ||
        c + a < b) {
        cout << -1 << '\n';
        return 0;
    }
    ld len = sqrt((a * a + b * b + c * c ) / 2 + 2 * sqrt(3) * tri_area(a, b, c));
    if (len > a + b ||
        len > b + c ||
        len > c + a) {
        cout << -1 << '\n';
        return 0;
    }
    ld area = len * len * sqrt(3) / 4,
        area_ab = tri_area(a, b, len),
        area_bc = tri_area(b, c, len),
        area_ca = tri_area(c, a, len),
        area2 = area_ab + area_bc + area_ca;
    if (abs(area - area2) > EPS) {
        cout << -1 << '\n';
        return 0;
    }
    cout << fixed << setprecision(10) << area << '\n';

    return 0;
}