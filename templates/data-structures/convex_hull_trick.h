#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define sz(C) (ll) C.size()
#define pb push_back

const ll INF = 4e18;

struct Line {
    ll m, b;        // y = mx + b
    ld x_left;      // intersection with previous line
    Line(ll _m = 0, ll _b = INF) : m(_m), b(_b), x_left(-1e18) {}
    // evaluate at integer x
    inline ll val(ll x) const { return m * x + b; }
    // intersection point (as double) with other line
    static ld isect(const Line &p, const Line &q) {
        // assumes p.m < q.m
        return (ld) (q.b - p.b) / (p.m - q.m);
    }
};

// -----------------------------------------------------------------------------
//  Convex Hull Trick
// -----------------------------------------------------------------------------
//  Supports:   - add_line(m, b)   insert y = m x + b
//              - query(x)         minimum y at x for all lines
//  Restrictions:
//              - Lines MUST be added in strictly monotone order of slope
//                (increasing for a lower hull / min queries).
//              - Query points x MUST be non-decreasing.
//                (If queries are arbitrary, use binary-search version below.)
//  Complexity:  O(1) amortised per operation with the above monotone guarantees
//               Memory   O(# of lines)
//  Notes:      - Works with 64-bit integers as long as no overflow occurs in
//                m * x + b.  For safer usage with large coordinates, switch
//                to long double.
//              - swap max/min by flipping sign of m and b (or by inverting
//                inequality in isect()).
// -----------------------------------------------------------------------------
struct ConvexHullTrick {
    deque<Line> hull;   // lower hull (for min queries)

    // insert line with strictly higher slope than last inserted
    void add_line(Line nw) {
        // remove last line if it's useless
        while (sz(hull) >= 1) {
            ld x = Line::isect(hull.back(), nw);
            if (x <= hull.back().x_left) hull.pop_back();
            else { nw.x_left = x; break; }
        }
        if (hull.empty()) nw.x_left = -1e18;
        hull.pb(nw);
    }

    void add_line(ll m, ll b) {
        add_line(Line(m, b));
    }

    // min y at query point x (x must be non-decreasing across calls)
    ll query(ll x) {
        assert(!hull.empty());
        while (sz(hull) >= 2 && hull[1].x_left <= x) hull.pop_front();
        return hull.front().val(x);
    }
};

// -----------------------------------------------------------------------------
//  Binary-search variant (no monotone query order required)
// --------------------------------------------------------------------------
//  Same usage but query(x) is O(log n). Lines still must be added with
//  increasing slope. Internally stores breakpoints to enable binary search.
// -----------------------------------------------------------------------------
struct CHT_BinSearch  {
    vector<Line> lines;

    void add_line(Line nw) {
        while (!lines.empty()) {
            ld x = Line::isect(lines.back(), nw);
            if (x <= lines.back().x_left) lines.pop_back();
            else { nw.x_left = x; break; }
        }
        if (lines.empty()) nw.x_left = -1e18;
        lines.pb(nw);
    }

    void add_line(ll m, ll b) {
        add_line(Line(m, b));
    }

    ll query(ll x) const {
        assert(!lines.empty());
        int l = 0, r = sz(lines) - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (lines[mid + 1].x_left <= x) l = mid + 1;
            else                            r = mid;
        }
        return lines[l].val(x);
    }
};
