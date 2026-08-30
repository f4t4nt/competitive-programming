#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ld, ld> pld;

#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()

// -----------------------------------------------------------------------------
//  Polygon Toolkit
// -----------------------------------------------------------------------------
//  Supports:   - cross, shoelace, get_com, make_ccw, in_triangle
//              - extend, angle, proj
//  Coordinates: pld = {x, y}, ld throughout
// -----------------------------------------------------------------------------
// (b - a) x (c - a); > 0 means a->b->c turns left
ld cross(pld a, pld b, pld c) {
    return (b.first - a.first) * (c.second - a.second) -
           (b.second - a.second) * (c.first - a.first);
}

// unsigned area of a simple polygon, either orientation
ld shoelace(vector<pld> &v) {
    ld rv = 0;
    for (ll i = 0; i < sz(v); i++) {
        auto [x1, y1] = v[i];
        auto [x2, y2] = v[(i + 1) % sz(v)];
        rv += x1 * y2 - y1 * x2;
    }
    return abs(rv) / 2;
}

// center of mass of a simple polygon, uniform density
pld get_com(vector<pld> &poly) {
    ld x = 0, y = 0, area = 0;
    for (ll i = 0; i < sz(poly); i++) {
        auto [x1, y1] = poly[i];
        auto [x2, y2] = poly[(i + 1) % sz(poly)];
        ld a = x1 * y2 - x2 * y1;
        area += a;
        x += (x1 + x2) * a;
        y += (y1 + y2) * a;
    }
    return {x / (3 * area), y / (3 * area)};
}

// sort vertices by angle around the centroid (ascending atan2 = ccw);
// recovers a convex polygon from its shuffled vertices
void make_ccw(vector<pld> &points) {
    ld cx = 0, cy = 0;
    for (auto [x, y] : points) cx += x, cy += y;
    cx /= sz(points), cy /= sz(points);
    sort(all(points), [&](pld a, pld b) {
        return atan2(a.second - cy, a.first - cx) < atan2(b.second - cy, b.first - cx);
    });
}

// inside or on boundary, triangle in either orientation
bool in_triangle(pld p, vector<pld> &t) {
    vector<ld> d(3);
    for (ll i = 0; i < 3; i++) d[i] = cross(t[i], t[(i + 1) % 3], p);
    return (d[0] >= 0 && d[1] >= 0 && d[2] >= 0) || (d[0] <= 0 && d[1] <= 0 && d[2] <= 0);
}

// extend p1 away from p0 by r
pld extend(pld p0, pld p1, ld r) {
    ld dx = p1.first - p0.first, dy = p1.second - p0.second;
    ld d = sqrt(dx * dx + dy * dy);
    dx /= d, dy /= d;
    return {p1.first + dx * r, p1.second + dy * r};
}

// signed angle between vecs p0p1 and p0p2
ld angle(pld p0, pld p1, pld p2) {
    ld wx = p1.first - p0.first, wy = p1.second - p0.second,
       vx = p2.first - p0.first, vy = p2.second - p0.second;
    return atan2(wy * vx - wx * vy, wx * vx + wy * vy);
}

// project p2 onto line p0p1
pld proj(pld p0, pld p1, pld p2) {
    ld wx = p1.first - p0.first, wy = p1.second - p0.second,
       vx = p2.first - p0.first, vy = p2.second - p0.second;
    ld k = (wx * vx + wy * vy) / (wx * wx + wy * wy);
    return {p0.first + wx * k, p0.second + wy * k};
}
