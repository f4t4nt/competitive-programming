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

ld pow(ld x, ll n) {
    ld res = 1;
    while (n > 0) {
        if (n & 1) res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

ld probability_a_before_b(ld a, ld b, ld s, ld p) {
    if (s == a) {
        return 1;
    } elif (s == b) {
        return 0;
    } elif (s < a && a < b) {
        return 1;
    } elif (s < b && b < a) {
        return 0;
    } elif (a < b && b < s) {
        return 0;
    } elif (b < a && a < s) {
        return 1;
    } else {
        ld q = p / (1 - p);
        if (q == 1) {
            return (ld) (s - b) / (a - b);
        } else {
            return (pow(q, a - s) * (1 - pow(q, s - b))) / (1 - pow(q, a - b));
        }
    }
}

ll bitcount(ll x) {
    ll rv = 0;
    while (x) {
        rv++;
        x &= x - 1;
    }
    return rv;
}

int main() {
    ll a = 20, b = 10;
    ld pro = 0.4;
    map<ll, ld> test;
    FOR (i, 100) {
        test[i] = probability_a_before_b(a, b, i, pro);
    }

    ll n;
    cin >> n;
    vector<ld> p(n);
    FOR (i, n) {
        cin >> p[i];
    }
    vector<ll> s(n + 1);
    FOB (i, 1, n + 1) {
        cin >> s[i];
    }
    vector<ld> dp(1 << n);
    dp[0] = 1;
    FOB (i, 1, 1 << n) {
        ll c = bitcount(i);
        ll prev_s = s[c - 1], curr_s = s[c];
        FOR (j, n) {
            if (i & (1 << j)) {
                ll prev = i ^ (1 << j);
                dp[i] = max(dp[i],
                    dp[prev] * probability_a_before_b(curr_s, -curr_s, prev_s, p[j]) +
                    (1 - dp[prev]) * probability_a_before_b(curr_s, -curr_s, -prev_s, p[j]));
            }
        }
    }
    cout << fixed << setprecision(18) << dp[(1 << n) - 1] << '\n';
    return 0;
}