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

constexpr ll MOD = 998244353;

// ll count(ll x) {
//     if (x < 0) {
//         return 0;
//     } elif (x == 0) {
//         return 1;
//     }
//     vector<ll> digits;
//     while (x > 0) {
//         digits.pb(x % 10);
//         x /= 10;
//     }
//     flip(digits);
//     vector<vector<ll>> dp(sz(digits), vector<ll>(10, 0));
//     FOB (i, 1, digits[0]) {
//         dp[0][i] = 1;
//     }
//     bool valid = true;
//     FOB (i, 1, sz(digits)) {
//         ll sum = 0;
//         FOR (j, 10) {
//             sum += dp[i - 1][j];
//         }
//         FOR (j, 10) {
//             dp[i][j] = sum - dp[i - 1][j];
//         }
//         FOB (j, 1, 10) {
//             dp[i][j]++;
//         }
//         if (valid) {
//             FOR (j, digits[i]) {
//                 if (j != digits[i - 1]) {
//                     dp[i][j]++;
//                 }
//             }
//         }
//         if (digits[i] == digits[i - 1]) {
//             valid = false;
//         }
//     }
//     ll rv = 1 + valid;
//     FOR (i, 10) {
//         rv += dp[sz(digits) - 1][i];
//     }
//     return rv;
// }

ll count(str x) {
    if (x == "0") {
        return 1;
    }
    vector<ll> digits;
    FORE (i, x) {
        digits.pb(i - '0');
    }
    vector<ll> dp0(10, 0);
    FOB (i, 1, digits[0]) {
        dp0[i] = 1;
    }
    bool valid = true;
    FOB (i, 1, sz(digits)) {
        vector<ll> dp1(10, 0);
        ll sum = 0;
        FOR (j, 10) {
            sum = (sum + dp0[j]) % MOD;
        }
        FOR (j, 10) {
            dp1[j] = (sum - dp0[j] + MOD) % MOD;
        }
        FOB (j, 1, 10) {
            dp1[j] = (dp1[j] + 1) % MOD;
        }
        if (valid) {
            FOR (j, digits[i]) {
                if (j != digits[i - 1]) {
                    dp1[j] = (dp1[j] + 1) % MOD;
                }
            }
        }
        if (digits[i] == digits[i - 1]) {
            valid = false;
        }
        dp0 = dp1;
    }
    ll rv = 1 + valid;
    FOR (i, 10) {
        rv = (rv + dp0[i]) % MOD;
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    str a, b;
    cin >> a >> b;
    FORR (i, sz(a)) {
        if (a[i] == '0') {
            a[i] = '9';
        } else {
            a[i]--;
            break;
        }
    }
    cout << (count(b) - count(a) + MOD) % MOD << '\n';

    return 0;
}