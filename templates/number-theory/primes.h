#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define pb push_back

const ll MAXN = 1e6 + 1;

// -----------------------------------------------------------------------------
//  Sieve of Eratosthenes
// -----------------------------------------------------------------------------
//  Returns:    all primes below MAXN
//  Complexity: O(MAXN log log MAXN)
// -----------------------------------------------------------------------------
vector<ll> get_primes() {
    vector<ll> primes;
    bitset<MAXN> is_prime;
    is_prime.set();
    for (ll i = 2; i < MAXN; i++) {
        if (is_prime[i]) {
            primes.pb(i);
            for (ll j = i * i; j < MAXN; j += i) is_prime[j] = 0;
        }
    }
    return primes;
}
