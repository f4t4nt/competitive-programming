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

constexpr ll MOD = 1e9 + 7;
constexpr ll MAX_N = 1e3;

ll fact[MAX_N + 1];
ll inv_fact[MAX_N + 1];
ll inv[MAX_N + 1];
ll choose[MAX_N + 1][MAX_N + 1];

void init() {
    fact[0] = 1;
    inv_fact[0] = 1;
    inv[1] = 1;
    for (ll i = 1; i <= MAX_N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        if (i > 1) {
            inv[i] = (MOD - (MOD / i) * inv[MOD % i] % MOD) % MOD;
        }
        inv_fact[i] = (inv_fact[i - 1] * inv[i]) % MOD;
    }
    for (ll i = 0; i <= MAX_N; i++) {
        for (ll j = 0; j <= i; j++) {
            choose[i][j] = (fact[i] * inv_fact[j] % MOD) * inv_fact[i - j] % MOD;
        }
    }
}

int main() {
    init();
    ll t;
    cin >> t;
    while (t--) {
        ll n, i, j, x, y, rv = 0;
        cin >> n >> i >> j >> x >> y;
        if (x > y) {
            swap(x, y);
            swap(i, j);
            i = n + 1 - i;
            j = n + 1 - j;
        }
        if (i == x && j == y) {
            rv = MOD - 1;
        }
        if (y == n) {
            rv += (choose[x - 1][i - 1] * choose[n - x - 1][j - i - 1]) % MOD;
            rv %= MOD;
        } else {
            ll tmp = y + j - n - i - 1;
            if (tmp >= 0) {
                FOB (k, i + 1, j) {
                    rv += (((choose[x - 1][i - 1] *
                        choose[n - y - 1][j - k - 1]) % MOD) *
                        choose[y - x - 1][tmp]) % MOD;
                    rv %= MOD;
                }
            }
            FOB (k, j + 1, n + 1) {
                rv += (((choose[x - 1][i - 1] *
                    choose[y - x - 1][j - i - 1]) % MOD) *
                    choose[n - y - 1][k - j - 1]) % MOD;
                rv %= MOD;
            }
        }
        cout << rv << '\n';
    }
    return 0;
}