#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

// a * x + b * y = gcd(a, b)

pair<ll, ll> bezout(ll a, ll b) {
    if (a == 0) return {0, 1};
    auto [x, y] = bezout(b % a, a);
    return {y - (b / a) * x, x};
}

// x % m == a, x % n == b
// x % lcm(m, n) = -(a * v * n + b * u * m) / gcd(m, n)

ll crt(ll m, ll n, ll a, ll b) {
    ll g = gcd(m, n);
    if (a % g != b % g) return -1;
    ll lcm = m * n / g;
    auto [u, v] = bezout(m / g, n / g);
    ll k = (b - a) / g;
    ll x = (a + m * k * u) % lcm;
    if (x < 0) x += lcm;
    return x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll a, b, c, d, e, f, g;
    cin >> a >> b >> c >> d >> e >> f >> g;
    set<ll> volumes;
    FOR (i, min(a, b) / 2 + 1) {
        volumes.insert(i * (a - 2 * i) * (b - 2 * i));
    }
    auto it = volumes.rbegin();
    vector<ll> max_v;
    FOR (i, 3) {
        max_v.pb(*it);
        it++;
    }

    // solve
    // x % max_v == c
    // x % max_v_2 == d
    // x % max_v_3 == e
    // f <= x <= g

    ll x = crt(max_v[0], max_v[1], c, d);
    ll max_v_lcm = max_v[0] * max_v[1] / gcd(max_v[0], max_v[1]);
    ll y = x % max_v_lcm;
    x = crt(max_v_lcm, max_v[2], y, e);
    max_v_lcm = max_v_lcm * max_v[2] / gcd(max_v_lcm, max_v[2]);
    y = x % max_v_lcm;
    x = f + ((y - f) % max_v_lcm + max_v_lcm) % max_v_lcm;
    cout << x << '\n';

    return 0;
}