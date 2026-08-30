#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

#define sz(C) (ll) C.size()

const ld PI = acosl(-1);

// -----------------------------------------------------------------------------
//  FFT (complex)
// -----------------------------------------------------------------------------
//  Supports:    fft(a, inv), in-place iterative Cooley-Tukey; inv = true
//               inverts
//  Restrictions:
//              - sz(a) must be a power of two
//              - results come back as ld: round real parts to nearest ll;
//                trustworthy while output coefficients stay under ~1e15
//                (exact arithmetic: use the mod version below)
//  Complexity:  O(n log n)
//  Usage (c = a * b as polynomials, deg sum = n):
//      ll n2 = 1LL << (64 - __builtin_clzll(n));
//      vector<cd> a(n2), b(n2);
//      ...init a, b...
//      fft(a, false);
//      fft(b, false);
//      for (ll i = 0; i < n2; i++) a[i] *= b[i];
//      fft(a, true);
// -----------------------------------------------------------------------------
void fft(vector<cd> &a, bool inv) {
    ll n = sz(a);
    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (ll len = 2; len <= n; len <<= 1) {
        ld ang = 2 * PI / len * (inv ? -1 : 1);
        cd wlen(cosl(ang), sinl(ang));
        for (ll i = 0; i < n; i += len) {
            cd w(1);
            for (ll j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (inv) for (auto &x : a) x /= n;
}

// -----------------------------------------------------------------------------
//  NTT (exact, mod 998244353)
// -----------------------------------------------------------------------------
//  Supports:    fft(a, inv) on vector<ll>, same shape as above but over
//               Z_MOD, no precision loss
//  Restrictions:
//              - sz(a) a power of two, at most ROOT_PW
//              - entries already reduced into [0, MOD)
//  Complexity:  O(n log n)
// -----------------------------------------------------------------------------
const ll MOD = 998244353;       // 119 * 2^23 + 1, primitive root 3
const ll ROOT = 15311432;       // 3^119, has order 2^23 (mod MOD)
const ll ROOT_1 = 469870224;    // ROOT * ROOT_1 = 1 (mod MOD)
const ll ROOT_PW = 1LL << 23;   // ROOT^ROOT_PW = 1 (mod MOD)

ll modpow(ll b, ll e, ll mod) {
    ll rv = 1;
    b %= mod;
    while (e) {
        if (e & 1) rv = rv * b % mod;
        b = b * b % mod;
        e >>= 1;
    }
    return rv;
}

void fft(vector<ll> &a, bool inv) {
    ll n = sz(a);
    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (ll len = 2; len <= n; len <<= 1) {
        ll wlen = (inv ? ROOT_1 : ROOT);
        for (ll i = len; i < ROOT_PW; i <<= 1) wlen = wlen * wlen % MOD;
        for (ll i = 0; i < n; i += len) {
            ll w = 1;
            for (ll j = 0; j < len / 2; j++) {
                ll u = a[i + j], v = a[i + j + len / 2] * w % MOD;
                a[i + j] = (u + v < MOD ? u + v : u + v - MOD);
                a[i + j + len / 2] = (u - v >= 0 ? u - v : u - v + MOD);
                w = w * wlen % MOD;
            }
        }
    }
    if (inv) {
        ll n_1 = modpow(n, MOD - 2, MOD);
        for (ll &x : a) x = x * n_1 % MOD;
    }
}
