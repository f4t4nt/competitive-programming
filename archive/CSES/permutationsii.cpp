#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
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

bool ok(vector<ll> &perm) {
    FOR (i, sz(perm) - 1) {
        if (abs(perm[i] - perm[i + 1]) == 1) {
            return false;
        }
    }
    return true;
}

ll cnt(ll &n) {
    vector<ll> perm(n);
    iota(all(perm), 0);
    ll rv = 0;
    do {
        rv += ok(perm);
    } while (next_permutation(all(perm)));
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<ll> dp(n + 1);
    dp[0] = dp[1]= 1;
    dp[2] = dp[3] = 0;
    FOB (i, 4, n + 1) {
        dp[i] = ((i + 1) * dp[i - 1]) % MOD;
        dp[i] = ((dp[i] - (i - 2) * dp[i - 2]) % MOD + MOD) % MOD;
        dp[i] = ((dp[i] - (i - 5) * dp[i - 3]) % MOD + MOD) % MOD;
        dp[i] = (dp[i] + (i - 3) * dp[i - 4]) % MOD;
    }
    cout << dp[n] << '\n';

    return 0;
}