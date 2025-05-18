#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1e9 + 7;

struct mll {
    ll v;
    mll(): v(0) {}
    mll(ll _v) { v = (_v % MOD + MOD) % MOD; }
    explicit operator ll() const { return v; }
    mll& operator+=(const mll &o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
    mll& operator-=(const mll &o) { v -= o.v; if (v < 0) v += MOD; return *this; }
    mll& operator*=(const mll &o) { v = (ll)(v * o.v % MOD); return *this; }
    mll& operator/=(const mll &o) { return *this *= o.inv(); }
    friend mll operator+(mll a, const mll &b) { return a += b; }
    friend mll operator-(mll a, const mll &b) { return a -= b; }
    friend mll operator*(mll a, const mll &b) { return a *= b; }
    friend mll operator/(mll a, const mll &b) { return a /= b; }
    mll operator-() const { return mll(-v); }
    bool operator==(const mll &o) const { return v == o.v; }
    bool operator!=(const mll &o) const { return v != o.v; }
    static mll pow(mll a, ll e) {
        mll r = 1;
        while (e > 0) {
            if (e & 1) r *= a;
            a *= a;
            e >>= 1;
        }
        return r;
    }
    mll inv() const { return pow(*this, MOD - 2); }
    friend ostream& operator<<(ostream &os, const mll &m) { return os << m.v; }
    friend istream& operator>>(istream &is, mll &m) { ll x; is >> x; m = mll(x); return is; }
};

struct NumTheory {
    ll N;
    vector<mll> fac, ifac, inv;
    vector<mll> catalan, der, H;

    NumTheory(ll _N): N(_N),
        fac(N + 1), ifac(N + 1), inv(N + 1),
        catalan(N / 2 + 1), der(N + 1), H(N + 1)
    {
        // factorial / inverse factorial / inverse
        fac[0] = 1;
        for (ll i = 1; i <= N; i++) fac[i] = fac[i - 1] * mll(i);
        ifac[N] = fac[N].inv();
        for (ll i = N; i >= 1; i--) ifac[i - 1] = ifac[i] * mll(i);
        for (ll i = 1; i <= N; i++) inv[i] = ifac[i] * fac[i - 1];

        // Catalan numbers
        catalan[0] = 1;
        for (ll n = 1; n <= N / 2; n++)
            catalan[n] = choose(2 * n, n) / mll(n + 1);

        // derangement d[n] = (n - 1) (d[n - 1] + d[n - 2])
        der[0] = 1; if (N) der[1] = 0;
        for (ll n = 2; n <= N; n++)
            der[n] = mll(n - 1) * (der[n - 1] + der[n - 2]);

        // harmonic numbers H_n = sum (1 / i)
        H[0] = 0;
        for (ll i = 1; i <= N; i++) H[i] = H[i - 1] + inv[i];
    }

    mll choose(ll n, ll k) {
        if (k < 0 || k > n) return 0;
        return fac[n] * ifac[k] * ifac[n-k];
    }

    // Lucas theorem for huge n, k
    mll choose_lucas(ll n,ll k) {
        if (k < 0 || k > n) return 0;
        mll res = 1;
        while (n || k) {
            ll ni = n % MOD;
            ll ki = k % MOD;
            if (ki > ni) return 0;
            res *= choose(ni, ki);
            n /= MOD; k /= MOD;
        }
        return res;
    }

    mll perm(ll n,ll k) const{
        if (k < 0 || k > n) return 0;
        return fac[n] * ifac[n-k];
    }

    // discrete logarithm by baby-step giant-step O(sqrt(MOD))
    ll dlog(mll a, mll b) {
        ll m = (ll) ceil(sqrt(MOD));
        unordered_map<ll, ll> table;
        mll e = 1;
        for (ll j = 0; j < m; ++j) {
            table[(ll) e] = j;
            e *= a;
        }
        mll factor = mll::pow(a, MOD - 1 - m);
        mll gamma = b;
        for (ll i = 0; i < m; i++) {
            auto it = table.find((ll) gamma);
            if (it != table.end())
                return i * m + it->second;
            gamma *= factor;
        }
        return -1; // no solution
    }
};
