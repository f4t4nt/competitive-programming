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

const ll MAX = 6e6;
vector<ll> primes, prime_sum = {0};
bitset<MAX + 1> is_comp;

ll solve(ll n) {
    vector<ll> a(n), pre(n + 1);
    for (ll &x : a) cin >> x;
    rsort(a);
    for (ll i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + a[i];
    }
    ll best = 0;
    for (ll m = n; m >= 0; m--) {
        if (prime_sum[m] <= pre[m]) {
            best = m;
            break;
        }
    }
    return n - best;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    for (ll p = 2; p <= MAX; p++) {
        if (!is_comp[p]) {
            primes.pb(p);
            prime_sum.pb(prime_sum.back() + p);
            for (ll q = p * 2; q <= MAX; q += p) {
                is_comp[q] = 1;
            }
        }
    }

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        cout << solve(n) << '\n';
    }

    return 0;
}