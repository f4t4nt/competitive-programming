#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

// -----------------------------------------------------------------------------
//  Binary search on a monotone predicate
// -----------------------------------------------------------------------------
//  Supports:   - first_true(lo, hi, f)   f looks like F F F T T T,
//                                          first T, hi if all F
//              - last_true(lo, hi, f)    f looks like T T T F F F,
//                                          last T, lo - 1 if all F
//  Restrictions:
//              - search space is the half-open [lo, hi); f is never called
//                outside it
//  Notes:      - invariant (first_true): f false on [original lo, lo), true
//                on [hi, original hi)
//              - mid = lo + (hi - lo) / 2 rounds toward lo, no overflow, ok
//                for negative bounds
//  Usage: ll k = first_true(1, n + 1, [&](ll x) { return x * x >= n; });
// -----------------------------------------------------------------------------

template<typename F>
ll first_true(ll lo, ll hi, F f) {
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (f(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

// first false minus one; the T...TF...F mirror of first_true
template<typename F>
ll last_true(ll lo, ll hi, F f) {
    return first_true(lo, hi, [&](ll x) { return !f(x); }) - 1;
}

// real boundary of F...T on [lo, hi]: 100 halvings, returns a true point with
// false just below (assumes f(hi) true; if f all false, hi comes back unchanged)
template<typename F>
ld first_true_real(ld lo, ld hi, F f) {
    for (ll i = 0; i < 100; i++) {
        ld mid = (lo + hi) / 2;
        if (f(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}
