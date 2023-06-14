#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <string.h>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

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

constexpr ll PRIME_MAX = 10000;

int main() {
    ll t;
    cin >> t;
    vector<bool> is_prime(PRIME_MAX, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i < PRIME_MAX; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j < PRIME_MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }
    vector<ll> primes;
    FOR (i, PRIME_MAX) {
        if (is_prime[i]) {
            primes.pb(i);
        }
    }
    while (t--) {
        ll n;
        cin >> n;
        set<ll> s;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
            s.insert(a[i]);
        }
        if (sz(s) != n) {
            cout << "NO\n";
            continue;
        }
        bool valid = true;
        FORE (prime, primes) {
            vector<ll> residues(prime);
            FOR (i, n) {
                residues[a[i] % prime]++;
            }
            bool invalid = true;
            FOR (i, prime) {
                if (residues[i] < 2) {
                    invalid = false;
                    break;
                }
            }
            if (invalid) {
                valid = false;
                break;
            }
        }
        cout << (valid ? "YES\n" : "NO\n");
    }
    return 0;
}