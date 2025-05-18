#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

template<class T>
struct SparseTable {
    ll n, K;                // n = array size, K = floor(log2(n)) + 1
    vector<vector<T>> st;   // st[k][i] = op over [i, i + 2^k)
    vector<ll> log2s;       // log2s[i] = floor(log2(i))
    bool idempotent;        // whether the op is idempotent (e.g. min, max, gcd)

    // combine two values
    static T combine(const T &a, const T &b) {
        return a + b;  // example: sum; change to max(a, b) for RMQ
    }

    SparseTable(const vector<T> &a, bool _idempotent)
        : n(a.size()), idempotent(_idempotent)
    {
        K = 64 - __builtin_clzll(n);      // ceil(log2(n))
        st.assign(K, vector<T>(n));
        log2s.assign(n + 1, 0);
        for (ll i = 2; i <= n; i++) log2s[i] = log2s[i >> 1] + 1;

        // base level
        st[0] = a;

        // build sparse table
        for (ll k = 1; k < K; k++) {
            for (ll i = 0; i + (1LL << k) <= n; i++) {
                st[k][i] = combine(st[k - 1][i],
                                   st[k - 1][i + (1LL << (k - 1))]);
            }
        }
    }

    // query [l, r)
    T qry(ll l, ll r) const {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return T{}; // optional: empty interval = neutral value
        ll len = r - l;
        if (idempotent) {
            ll k = log2s[len];
            return combine(st[k][l], st[k][r - (1LL << k)]);
        } else {
            T res = T{};
            for (ll k = K - 1; k >= 0; k--) {
                if ((1LL << k) <= len) {
                    res = (res == T{}) ? st[k][l] : combine(res, st[k][l]);
                    l += (1LL << k);
                    len -= (1LL << k);
                }
            }
            return res;
        }
    }
};