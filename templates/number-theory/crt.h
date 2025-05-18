#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

// gcd(a, b)
ll gcd(ll a, ll b) {
    return a == 0 ? b : gcd(b % a, a);
}

// lcm(a, b)
ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

// extended Euclidean algorithm: returns (x, y) s.t. a * x + b * y = gcd(a, b)
pll bezout(ll a, ll b) {
    if (a == 0) return {0, 1};
    auto [x, y] = bezout(b % a, a);
    return {y - (b / a) * x, x};
}

// Chinese Remainder Theorem: solves x ≡ a (mod m), x ≡ b (mod n)
// Returns smallest non-negative x < lcm(m, n), or -1 if no solution
ll crt(ll m, ll n, ll a, ll b) {
    ll g = gcd(m, n);
    if ((a - b) % g != 0) return -1;
    ll lcm = m / g * n;
    auto [u, v] = bezout(m / g, n / g);
    ll k = (b - a) / g;
    ll x = (a + m * k % lcm * u % lcm) % lcm;
    if (x < 0) x += lcm;
    return x;
}

// Chinese Remainder Theorem: solves x ≡ a (mod m), x ≡ b (mod n)
// Returns pair {x, mod} with x ≡ rem (mod mod), or {-1, -1} if no solution
pll solve_crt(const vector<pll> &mods_rems) {
    ll x = 0, mod = 1;
    for (auto [m, r] : mods_rems) {
        ll nx = crt(mod, m, x, r);
        if (nx == -1) return {-1, -1};
        mod = lcm(mod, m);
        x = nx;
    }
    return {x, mod};
}
