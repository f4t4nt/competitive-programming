#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define pb push_back

// (b - a) x (c - a); > 0 means a->b->c turns left
ll cross(pll a, pll b, pll c) {
    return (b.first - a.first) * (c.second - a.second) -
           (b.second - a.second) * (c.first - a.first);
}

// -----------------------------------------------------------------------------
//  Convex hull (monotone chain)
// -----------------------------------------------------------------------------
//  Returns:     the hull in ccw order starting from the lowest-leftmost
//               point, collinear points dropped
//  Restrictions:
//              - Dedup points first: duplicates can leave a repeated vertex.
//              - cross() must not overflow: |coords| up to ~1.5e9 are safe.
//  Complexity:  O(n log n)
// -----------------------------------------------------------------------------
vector<pll> convex_hull(vector<pll> pts) {
    if (sz(pts) <= 1) return pts;
    sort(all(pts));
    vector<pll> lo, hi;
    for (auto &p : pts) {
        while (sz(lo) >= 2 && cross(lo[sz(lo) - 2], lo[sz(lo) - 1], p) <= 0) lo.pop_back();
        lo.pb(p);
    }
    for (auto it = pts.rbegin(); it != pts.rend(); it++) {
        while (sz(hi) >= 2 && cross(hi[sz(hi) - 2], hi[sz(hi) - 1], *it) <= 0) hi.pop_back();
        hi.pb(*it);
    }
    lo.pop_back(), hi.pop_back();
    lo.insert(lo.end(), all(hi));
    return lo;
}
