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

template<typename T> using indexed_set = tree<
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
// #define f first
// #define s second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll MOD = 1e9 + 7;

ll poww(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    const ll inv6 = poww(6, MOD - 2);

    ll t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        ll case1 = 0,  // [2, sqrt n]
            case2 = 0, // (sqrt n, n)
            case3 = 0; // [n, k]
        // case1
        ll i = 2;
        for (; i <= k && i * i <= n; i++) {
            vector<ll> v, pows;
            ll cur = n, cur_pow = 1;
            while (cur) {
                v.pb(cur % i);
                cur /= i;
                pows.pb(cur_pow);
                cur_pow = (cur_pow * i) % MOD;
            }
            ll vi = 0, pi = sz(v);
            while (pi--)
                case1 = (case1 + (v[vi++] * pows[pi]) % MOD) % MOD;
        }
        // case2
        while (i * i >= n) i--;
        for (; i >= 1; i--) {
            ll lo = n / (i + 1) + 1, hi = n / i + 1;
            hi = min(hi, k + 1);
            if (lo > k) break;
            if (lo >= hi || lo * lo <= n) continue;
            case2 = (case2 + i * (hi - lo) % MOD) % MOD;
            // for (ll j = lo; j < hi; j++) {
            //     case2 = (case2 + (n - i * j) * j % MOD) % MOD;
            // }
            ll tmp = inv6 * (hi - lo) % MOD,
                part1 = i * (2 * hi * hi % MOD + hi * (2 * lo - 3) % MOD + 2 * lo * lo % MOD - 3 * lo + 1) % MOD,
                part2 = 3 * n * (hi + lo - 1) % MOD;
            case2 = (case2 - tmp * (part1 - part2) % MOD) % MOD;
            case2 = (case2 + MOD) % MOD;
        }
        // case3
        if (k > n) case3 = ((k - n) % MOD) * n % MOD;
        cout << (case1 + case2 + case3) % MOD << '\n';
    }

    return 0;
}