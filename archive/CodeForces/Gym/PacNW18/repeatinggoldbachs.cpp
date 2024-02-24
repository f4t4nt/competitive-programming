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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    vector<ll> primes;
    bitset<1000001> is_prime;
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;
    for (ll i = 2; i <= 1000000; i++) {
        if (is_prime[i]) {
            primes.pb(i);
            for (ll j = i * i; j <= 1000000; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    ll n, cnt = 0; cin >> n;
    assert(n % 2 == 0);
    while (n >= 4) {
        FORE (p, primes) {
            if (p > n / 2) assert(0);
            if (is_prime[n - p]) {
                cnt++;
                n -= 2 * p;
                break;
            }
        }
    }
    cout << cnt << '\n';

    return 0;
}