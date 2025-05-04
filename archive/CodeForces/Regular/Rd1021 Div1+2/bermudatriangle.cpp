#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

ll exgcd(ll a, ll b, ll &x, ll &y){
    if (!b) { x = 1; y = 0; return a; }
    ll x1, y1; ll g = exgcd(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b); return g;
}

ll mod_inv(ll a, ll m){
    ll x, y; ll g = exgcd(a, m, x, y);
    if(g != 1) return -1;
    x %= m; if(x < 0) x += m;
    return x;
}

struct LinSol{ bool ok; ll t0, mod; };
LinSol solve_one(ll a, ll b, ll m){
    ll g = __gcd(a,m);
    if(b % g) return { false, 0, 0 };
    a /= g; b /= g; m /= g;
    ll inv = mod_inv((a % m + m) % m, m);
    ll t0 = (inv * ((b % m) + m)) % m;
    return { true, t0, m };
}

LinSol crt(ll a1, ll m1, ll a2, ll m2){
    ll x, y; ll g = exgcd(m1, m2, x, y);
    if((a2 - a1) % g) return { false, 0, 0};
    ll lcm = m1 / g * m2;
    ll t = a1 + x * (a2 - a1) / g % (m2 / g) * m1;
    ll t0 = (t % lcm + lcm) % lcm;
    return { true, t0, lcm };
}

ll eval(ll n, ll x, ll y, ll vx, ll vy){
    auto s1 = solve_one(vx, (-x) % n, n);
    auto s2 = solve_one(vy, (-y) % n, n);
    if(!s1.ok || !s2.ok) return -1;
    auto both = crt(s1.t0, s1.mod, s2.t0, s2.mod);
    return both.ok ? both.t0 : -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, x, y, vx, vy; cin >> n >> x >> y >> vx >> vy;
        ll gcdv = __gcd(vx, vy);
        vx /= gcdv, vy /= gcdv;
        ll t = eval(n, x, y, vx, vy);
        if (t == -1) {
            cout << -1 << '\n';
            continue;
        }
        assert((x + vx * t) % n == 0);
        assert((y + vy * t) % n == 0);
        ll tx = (x + vx * t) / n, ty = (y + vy * t) / n;
        ll ans = tx + ty + (tx + ty) / 2 + abs(tx - ty) / 2 - 2;
        cout << ans << '\n';
    }

    return 0;
}