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
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, x, y, d, rv;
    cin >> n;
    vector<int> min_prime(1e7 + 1), primes;
    for (ll i = 2; i <= 1e7; i++) {
        if (min_prime[i] == 0) {
            min_prime[i] = i;
            primes.pb(i);
        }
        FORE (prime, primes) {
            if (prime > min_prime[i] || prime * i > 1e7) {
                break;
            }
            min_prime[prime * i] = prime;
            if (i % prime == 0) {
                break;
            }
        }
    }
    while (n--) {
        cin >> x >> y;
        d = y - x;
        if (d == 1) {
            cout << -1 << '\n';
            continue;
        }
        rv = (int) 1e9;
        while (d > 1) {
            int prime = min_prime[d];
            rv = min(rv, (prime - x % prime) % prime);
            d /= prime;
        }
        cout << rv << '\n';
    }
    return 0;
}