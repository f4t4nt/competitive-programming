#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ld EPS = 1e-9;

// -----------------------------------------------------------------------------
//  2D Primitives
// -----------------------------------------------------------------------------
//  Supports:   - Point: + - * /, dot, cross, len, len2, EPS equality
//              - Circle: has(p), c1 & c2 intersection points
//  Coordinates: ld with EPS = 1e-9
// -----------------------------------------------------------------------------
struct Point {
    ld x, y;

    Point operator+(Point o) { return {x + o.x, y + o.y}; }
    Point operator-(Point o) { return {x - o.x, y - o.y}; }
    Point operator*(ld k)    { return {x * k, y * k}; }
    Point operator/(ld k)    { return {x / k, y / k}; }

    ld dot(Point o)   { return x * o.x + y * o.y; }
    ld cross(Point o) { return x * o.y - y * o.x; }  // > 0: o is ccw of this
    ld len2()         { return x * x + y * y; }
    ld len()          { return sqrt(len2()); }

    bool operator==(Point o) { return abs(x - o.x) < EPS && abs(y - o.y) < EPS; }
    bool operator!=(Point o) { return !(*this == o); }
};

struct Circle {
    Point c;    // center
    ld r;

    // p inside or on the circle
    bool has(Point p) { return (p - c).len() <= r + EPS; }

    // intersection points: empty if disjoint or nested, two otherwise
    // (equal when tangent); same circle gives one arbitrary point
    vector<Point> operator&(Circle o) {
        ld d = (o.c - c).len();
        if (d > r + o.r + EPS || d < abs(r - o.r) - EPS) return {};
        if (d < EPS && abs(r - o.r) < EPS) return {{c.x + r, c.y}};
        Point sum = o.c + c, diff = o.c - c, perp = {diff.y, -diff.x};
        ld cdi = (r * r - o.r * o.r) / (2 * diff.len2()),
           cpe = 0.5 * sqrt(max((ld) 0, 2 * (r * r + o.r * o.r) / diff.len2()
               - (r * r - o.r * o.r) * (r * r - o.r * o.r) / (diff.len2() * diff.len2()) - 1));
        return {sum * 0.5 + diff * cdi + perp * cpe, sum * 0.5 + diff * cdi - perp * cpe};
    }
};
