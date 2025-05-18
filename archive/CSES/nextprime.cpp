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

const ll MAXN = 1e6 + 1;

vector<ll> get_primes() {
    vector<ll> primes;
    bitset<MAXN> is_prime;
    is_prime.set();
    for (ll i = 2; i < MAXN; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j < MAXN; j += i) is_prime[j] = 0;
        }
    }
    return primes;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    auto primes = get_primes();

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        bitset<MAXN> is_prime; // [n, n + 1e6]
        is_prime.set();
        is_prime[0] = 0;
        for (ll p : primes) {
            ll start = (n + p - 1) / p * p;
            for (ll j = start; j < n + 1e6; j += p) {
                if (j == p) continue;
                is_prime[j - n] = 0;
            }
        }
        ll i = 0;
        while (i < 1e6 && !is_prime[i]) i++;
        cout << i + n << '\n';
    }

    return 0;
}
