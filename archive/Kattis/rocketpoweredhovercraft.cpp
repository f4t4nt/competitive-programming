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

// clockwise angle from (x1, y1) to (x0, y0) to (x2, y2)
ld angle(ld x1, ld y1, ld x0, ld y0, ld x2, ld y2) {
    ld dot = (x1 - x0) * (x2 - x0) + (y1 - y0) * (y2 - y0),
        det = (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0),
        rv = atan2(det, dot);
    if (rv < 0) {
        rv += 2 * M_PI;
    }
    return rv;
}

ld get_time(ld &theta, ld &x, ld &y, ld &r, ld &v, ld &w) {
    ld spin_time = theta / w;

    ld x_ = x * cos(theta) + y * sin(theta),
        y_ = -x * sin(theta) + y * cos(theta);

    assert(y_ >= 0);

    if (x_ * x_ + (y_ - r) * (y_ - r) < r * r - 1e-3) {
        return 1e18;
    }

    ld line_d = sqrt(max((ld) 0, x_ * x_ + (y_ - r) * (y_ - r) - r * r));
    ld line_time = line_d / v;

    ld net_angle = angle(0, 0, 0, r, x_, y_),
        line_angle = atan2(line_d, r),
        arc_angle = net_angle - line_angle;
    
    ld arc_time = arc_angle / w;

    ld rv = spin_time + arc_time + line_time;
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ld x, y, v, w;
    cin >> x >> y >> v >> w;
    y = abs(y);
    ld r = v / w;
    ld rv = 1e18;

    for (ld theta = 0; theta <= atan2(y, x); theta += 1e-5) {
        rv = min(rv, get_time(theta, x, y, r, v, w));
    }

    cout << fixed << setprecision(10) << rv << '\n';

    return 0;
}