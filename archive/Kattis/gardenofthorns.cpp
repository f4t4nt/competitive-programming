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

ld area_circ(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3, ld r) {
    vector<ld> v12{x2 - x1, y2 - y1};
    vector<ld> v13{x3 - x1, y3 - y1};
    ld angle = abs(atan2(v12[0] * v13[1] - v13[0] * v12[1], v12[0] * v13[0] + v12[1] * v13[1]));
    if (angle > 180-0.0001) angle = 0;
    return r * r * angle / 2;
}
ld area_tri(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3) {
    return abs((x1*y2 + x2*y3 + x3*y1) - (y1*x2 + y2*x3 + y3*x1)) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n; ld r, w, h;
    cin >> n >> r >> w >> h;

    vector<vector<ld>> pts;
    FOR (i, n) {
        ld a, b, c;
        cin >> a >> b >> c;
        pts.pb(vector<ld>{a, b, c});
    }

    ld ans = 0;

    for (auto pt : pts) {
        ld x = pt[0], y = pt[1], v = pt[2];
        vector<ld> parts(4, 0);
        ld cur = 0;

        if (x - r >= 0) parts[0] += area_circ(x, y, 0, 0, 0, h, r);
        else if (x != 0) {
            ld offset = sqrt(r * r - x * x);
            if (y + offset >= h) parts[0] += area_tri(x, y, 0, y, 0, h);
            else parts[0] += area_tri(x, y, 0, y, 0, y + offset) + area_circ(x, y, 0, y + offset, 0, h, r);
            if (y - offset <= 0) parts[0] += area_tri(x, y, 0, y, 0, 0);
            else parts[0] += area_tri(x, y, 0, y, 0, y - offset) + area_circ(x, y, 0, y - offset, 0, 0, r);
        }

        if (x + r <= w) parts[1] += area_circ(x, y, w, 0, w, h, r);
        else if (x != w) {
            ld offset = sqrt(r * r - (x - w) * (x - w));
            if (y + offset >= h) parts[1] += area_tri(x, y, w, y, w, h);
            else parts[1] += area_tri(x, y, w, y, w, y + offset) + area_circ(x, y, w, y + offset, w, h, r);
            if (y - offset <= 0) parts[1] += area_tri(x, y, w, y, w, 0);
            else parts[1] += area_tri(x, y, w, y, w, y - offset) + area_circ(x, y, w, y - offset, w, 0, r);
        }

        if (y - r >= 0) parts[2] += area_circ(x, y, 0, 0, w, 0, r);
        else if (y != 0) {
            ld offset = sqrt(r * r - y * y);
            if (x + offset >= w) parts[2] += area_tri(x, y, x, 0, w, 0);
            else parts[2] += area_tri(x, y, x, 0, x + offset, 0) + area_circ(x, y, x + offset, 0, w, 0, r);
            if (x - offset <= 0) parts[2] += area_tri(x, y, x, 0, 0, 0);
            else parts[2] += area_tri(x, y, x, 0, x - offset, 0) + area_circ(x, y, x - offset, 0, 0, 0, r);
        }

        if (y + r <= h) parts[3] += area_circ(x, y, 0, h, w, h, r);
        else if (y != h) {
            ld offset = sqrt(r * r - (y - h) * (y - h));
            if (x + offset >= w) parts[3] += area_tri(x, y, x, h, w, h);
            else parts[3] += area_tri(x, y, x, h, x + offset, h) + area_circ(x, y, x + offset, h, w, h, r);
            if (x - offset <= 0) parts[3] += area_tri(x, y, x, h, 0, h);
            else parts[3] += area_tri(x, y, x, h, x - offset, h) + area_circ(x, y, x - offset, h, 0, h, r);
        }

        cur += parts[0] + parts[1] + parts[2] + parts[3];
        ans += v * cur;
    }

    cout << fixed << setprecision(10) << ans / (w * h) << endl;
    return 0;
}