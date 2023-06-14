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
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

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

ll calc(ch a, ch b) {
    if (a == '?' && b == '?') {
        return 26;
    } elif (a == '?' || b == '?') {
        return 1;
    } elif (a == b) {
        return 1;
    } else {
        return 0;
    }
}

void force(ll lo_a, ll hi_a, ll lo_b, ll hi_b, str &s, vector<ll> &dp) {
    ll val = 1;
    while (lo_a >= 0 && hi_a < lo_b && hi_b < sz(s) && val) {
        val = (val * calc(s[lo_a], s[lo_b])) % MOD;
        if (lo_a != hi_a) {
            val = (val * calc(s[hi_a], s[hi_b])) % MOD;
        }
        dp[(hi_b - lo_a + 1) / 2] = (dp[(hi_b - lo_a + 1) / 2] + 
            (val * dp[(lo_b - hi_a) / 2]) % MOD) % MOD;
        lo_a--, lo_b--, hi_a++, hi_b++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    str s;
    cin >> s;
    ll n = sz(s) / 2, rv = 1;
    if (sz(s) % 2 == 1) {
        if (s[n] == '?') {
            rv = 26;
        }
        s = s.substr(0, n) + s.substr(n + 1);
    }
    vector<ll> dp(n + 1);
    dp[0] = 1;
    ll lo = n - 1, hi = n, val = 1, idx = 1;
    while (lo >= 0 && hi < sz(s) && val) {
        if (s[lo--] == '?') {
            val = (val * 26) % MOD;
        }
        if (s[hi++] == '?') {
            val = (val * 26) % MOD;
        }
        dp[idx++] = val;
    }
    FOR (i, n) {
        lo = n - i - 1;
        hi = n + i;
        force(lo, lo, hi, hi, s, dp);
        force(lo - 1, lo, hi, hi + 1, s, dp);
    }
    rv = (rv * dp[n]) % MOD;
    cout << rv << '\n';
    
    return 0;
}