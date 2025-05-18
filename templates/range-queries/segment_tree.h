#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

template<class T>
struct SegTree {
    ll n, N;                // logical and padded length
    vector<T> data;         // segment values
    T def_val;              // neutral for combine

    // helpers
    static ll next_pow2(ll x) {
        return x <= 1 ? 1 : 1LL << (64 - __builtin_clzll(x - 1));
    }

    // combine two child node values
    static T combine(const T &a, const T &b) { return a + b; }

    // constructors
    SegTree(ll _n,
            const vector<T> &raw = {},
            T _def_val = T{})
        : n(_n), N(next_pow2(_n)),
          data(2 * N, _def_val), def_val(_def_val)
    {
        if (!raw.empty()) build(const_cast<vector<T>&>(raw));
    }

    // build / fill
    T build(const vector<T> &raw, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = N;
        if (r - l == 1) return data[i] = (l < n ? raw[l] : def_val);
        ll m = (l + r) / 2;
        return data[i] = combine(
            build(raw, 2 * i, l, m),
            build(raw, 2 * i + 1, m, r)
        );
    }

    void fill(vector<T> &vec, ll i = 1, ll l = 0, ll r = -1) {
        assert(sz(vec) == n);
        if (r == -1) r = N;
        if (r - l == 1) {
            if (l < n) vec[l] = data[i];
        } else {
            ll m = (l + r) / 2;
            fill(vec, 2 * i, l, m);
            fill(vec, 2 * i + 1, m, r);
        }
    }

    // point update
    void updi(ll ui, const T &val,
              ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = N;
        if (r - l == 1) { data[i] += val; return; }
        ll m = (l + r) / 2;
        if (ui < m) updi(ui, val, 2 * i, l, m);
        else        updi(ui, val, 2 * i + 1, m, r);
        data[i] = combine(data[2 * i], data[2 * i + 1]);
    }

    // range query [ql, qr)
    T qry(ll ql, ll qr,
          ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = N;
        if (qr <= l || r <= ql) return def_val;
        if (ql <= l && r <= qr) return data[i];
        ll m = (l + r) / 2;
        return combine(
            qry(ql, qr, 2 * i, l, m),
            qry(ql, qr, 2 * i + 1, m, r)
        );
    }

    // point query
    T qryi(ll qi, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = N;
        if (r - l == 1) return data[i];
        ll m = (l + r) / 2;
        return (qi < m) ? qryi(qi, 2 * i, l, m)
                        : qryi(qi, 2 * i + 1, m, r);
    }
};
