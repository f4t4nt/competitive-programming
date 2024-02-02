#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef string str;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

#define x first
#define y second

const ld PI = acos(-1);

pair<ld, ld> extend(pair<ld, ld> p0, pair<ld, ld> p1, ld r) {
    ld dx = p1.x - p0.x, dy = p1.y - p0.y;
    ld d = sqrt(dx * dx + dy * dy);
    dx /= d, dy /= d;
    return {p0.x + dx * r, p0.y + dy * r};
}

pair<ld, ld> proj(pair<ld, ld> p0, pair<ld, ld> p1, pair<ld, ld> p2) {
    pair<ld, ld> w = {p1.x - p0.x, p1.y - p0.y},
        v = {p2.x - p0.x, p2.y - p0.y};
    ld d= sqrt(w.x * w.x + w.y * w.y);
    w.x /= d, w.y /= d;
    return {p0.x + w.x * (w.x * v.x + w.y * v.y),
        p0.y + w.y * (w.x * v.x + w.y * v.y)};
}

ld dist(pair<ld, ld> p0, pair<ld, ld> p1) {
    return sqrt((p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y));
}

ld eval(pair<ld, ld> a, pair<ld, ld> b, pair<ld, ld> p) {
    return dist(a, p) + dist(b, p);
}

void tert(pair<ld, ld> a, pair<ld, ld> b, pair<ld, ld> c, ld r,
    ld lo, ld hi, ld &rv)
{
    while (abs(lo - hi) > 1e-9) {
        ld mid1 = (lo * 2 + hi) / 3, mid2 = (lo + hi * 2) / 3;
        pair<ld, ld> p1 = {c.x + r * cos(mid1), c.y + r * sin(mid1)},
            p2 = {c.x + r * cos(mid2), c.y + r * sin(mid2)};
        ld eval1 = eval(a, b, p1), eval2 = eval(a, b, p2);
        if (eval1 < eval2) {
            rv = eval1;
            hi = mid2;
        } else {
            rv = eval2;
            lo = mid1;
        }
    }
}

int main() {
    ll t; cin >> t;
    while (t--) {
        ld r;
        pair<ld, ld> a, b, c;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> r;
        if (dist(a, c) <= r && dist(b, c) <= r) {
            cout << fixed << setprecision(18) << dist(a, b) << '\n';
            continue;
        }
        // auto p = proj(a, b, c);
        // if (hypot(p.x - c.x, p.y - c.y) <= r) {
        //     cout << hypot(a.x - b.x, a.y - b.y) << '\n';
        // } else {
            
        //     cout << hypot(p.x - a.x, p.y - a.y) +
        //         hypot(p.x - b.x, p.y - b.y) << '\n';
        // }
        set<pair<ld, ld>> s;
        FOR (i, 360) {
            ld ang = (ld) i / 180 * PI;
            pair<ld, ld> p = {c.x + r * cos(ang), c.y + r * sin(ang)};
            s.insert({eval(a, b, p), ang});
        }
        auto it = s.begin();
        ld ang = it->second, rv = 1e18;
        tert(a, b, c, r, ang - 5 * PI / 180, ang + 5 * PI / 180, rv);
        cout << fixed << setprecision(18) << rv << '\n';
    }
}