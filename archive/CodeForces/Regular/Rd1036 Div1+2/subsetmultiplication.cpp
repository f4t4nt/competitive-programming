#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
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
// s.order_of_key(x) -> number of elements < x
// s.find_by_order(x) -> iterator to the x-th element (0-indexed)

#pragma GCC target("popcnt,lzcnt")
// __builtin_popcount(x) -> number of set bits
// __builtin_clz(x) -> number of leading zeros
// for ll, use __builtin_popcountll, __builtin_clzll

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define x first
#define y second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll LIM = 1e5;
vector<ll> primes;

void sieve() {
    bitset<100000> prime;
    prime.set();
    for (ll i = 2; i * i < LIM; i++)
        if (prime[i])
            for (ll j = i * i; j <= LIM; j += i)
                prime[j] = 0;
    for (ll i = 2; i <= LIM; i++)
        if (prime[i]) primes.pb(i);
}

void add_factor(map<ll, ll> &mp, ll p, ll e) {
    auto &cur = mp[p];
    if (e > cur) cur = e;
}

void factorize_and_update(ll x, map<ll, ll> &lcm_pf) {
    if (x == 1) return;
    for (ll p : primes) {
        if (p * p > x) break;
        if (x % p == 0) {
            ll cnt = 0;
            while (x % p == 0) x /= p, cnt++;
            add_factor(lcm_pf, p, cnt);
        }
    }
    if (x > 1) add_factor(lcm_pf, x, 1); 
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    sieve();

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> b(n);
        for (ll &x : b) cin >> x;
        map<ll, ll> lcm_pf;
        for (ll i = 0; i + 1 < n; i++) {
            if (b[i + 1] % b[i] == 0) continue;
            ll g = __gcd(b[i], b[i + 1]),
                p = b[i] / g;
            factorize_and_update(p, lcm_pf);
        }
        ll ans = 1;
        for (auto [p, e] : lcm_pf)
            for (ll i = 0; i < e; i++)
                ans *= p;
        cout << ans << '\n';
    }

    return 0;
}
