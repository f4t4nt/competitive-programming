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

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
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
#define x first
#define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

ll a, b, c, d; 

ll eval(ll i) {
    return (b / i - (a - 1) / i) * (d / i - (c - 1) / i);
}

// ll coeff(ll x, vector<ll> &primes) {
//     ll res = 1;
//     FORE(p, primes) {
//         if (p * p > x) break;
//         if (x % (p * p) == 0) return 0;
//         if (x % p == 0) {
//             res *= -1;
//             while (x % p == 0) x /= p;
//         }
//     }
//     if (x > 1) res *= -1;
//     return res;
// }

void dfs(ll prod, ll cnt, ll idx, vector<ll> &primes, ll &ans, bool add = true) {
    if (prod > b || prod > d || idx == sz(primes)) return;
    ans += (cnt & 1) ? -eval(prod) : eval(prod);
    FOB (jdx, idx + 1, sz(primes)) {
        if (prod * primes[jdx] > b || prod * primes[jdx] > d) break;
        dfs(prod * primes[jdx], cnt + 1, jdx, primes, ans, 1);
    }
}

const size_t MAX = 1e7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    bitset<MAX> sieve;
    vector<ll> primes = {1};
    for (ll i = 2; i < MAX; i++) {
        if (!sieve[i]) {
            primes.pb(i);
            for (ll j = i * i; j < MAX; j += i) {
                sieve[j] = 1;
            }
        }
    }

    cin >> a >> b >> c >> d;
    ll ans = 0;
    // FOB (i, 1, 1e7) {
    //     ans += coeff(i, primes) * eval(i);
    // }
    dfs(1, 0, 0, primes, ans);
    cout << ans << '\n';

    return 0;
}