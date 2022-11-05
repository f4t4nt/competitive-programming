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

constexpr ll MAX_N = 5e5 + 5;

int main() {
    vector<bool> is_prime(MAX_N, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i < MAX_N; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j < MAX_N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    vector<ll> primes;
    FOB (i, 2, MAX_N) {
        if (is_prime[i]) {
            primes.pb(i);
        }
    }
    ll n, x;
    cin >> n >> x;
    map<ll, ll> a;
    FOR (i, n) {
        ll y;
        cin >> y;
        a[y]++;
    }
    bool valid = true;
    while (sz(a) > 1 || a.begin()->second % (a.begin()->first + 1) == 0) {
        map<ll, ll> b;
        auto p = a.begin();
        if (p->second % (p->first + 1) != 0) {
            valid = false;
            break;
        }
        ll k = p->second / (p->first + 1);
        b[p->first + 1] = k;
        p++;
        while (p != a.end()) {
            b[p->first] += p->second;
            p++;
        }
        a = b;
    }
    valid &= a.begin()->first >= x;
    if (valid) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return 0;
}