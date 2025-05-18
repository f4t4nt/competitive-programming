#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

template<class T>
struct Fenwick {
    ll n;               // logical length (0-indexed externally)
    vector<T> bit;      // 1-based internal tree
    T def_val;          // neutral (usually 0 for +)

    // helpers
    static void combine(T &a, const T &b) { a += b; }               // point-update
    static T    prefix_op(const T &a, const T &b) { return a + b; } // query merge
    static T    inverse (const T &x) { return -x; }                 // for range

    // constructor
    Fenwick(ll _n,
            T _def_val = T{})                   // neutral element
        : n(_n),
          bit(n + 1, _def_val),
          def_val(_def_val) {}

    // point add (a[i] += delta)
    void upd(ll idx, const T &delta) {          // 0-based idx
        for (idx++; idx <= n; idx += idx & -idx)
            combine(bit[idx], delta);
    }

    // prefix sum (inclusive)
    T pref(ll idx) const {                      // 0-based idx
        T res = def_val;
        for (idx++; idx > 0; idx -= idx & -idx)
            res = prefix_op(res, bit[idx]);
        return res;
    }

    // range query [l, r] (inclusive)
    T qry(ll l, ll r) const {
        if (l > r) return def_val;
        return prefix_op(pref(r),
               prefix_op(inverse(pref(l - 1)), def_val));
    }
};

template<class T>
struct Fenwick2D {
    ll n, m;                        // logical sizes (0-based)
    vector<Fenwick<T>> bit;         // bit[x] is a 1-D Fenwick over y
    T def_val;

    Fenwick2D(ll _n, ll _m,
                       T _def_val = T{})
        : n(_n),
          m(_m),
          bit(n + 1, Fenwick<T>(_m, _def_val)),
          def_val(_def_val) {}

    // point add (a[x][y] += delta)
    void upd(ll x, ll y, const T &delta) {      // 0-based (x,y)
        for (x++; x <= n; x += x & -x)
            bit[x].upd(y, delta);
    }

    // prefix sum over rectangle [0..x, 0..y] (inclusive)
    T pref(ll x, ll y) const {
        T res = def_val;
        for (x++; x > 0; x -= x & -x)
            Fenwick<T>::combine(res, bit[x].pref(y));
        return res;
    }

    // range query over rectangle [x1..x2] x [y1..y2] (inclusive)
    T qry(ll x1, ll y1, ll x2, ll y2) const {
        return  pref(x2, y2)
              - pref(x1 - 1, y2)
              - pref(x2, y1 - 1)
              + pref(x1 - 1, y1 - 1);
    }
};