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

// hash of [l, r)
ll get_substr(ll l, ll r, vector<ll> &hash, vector<ll> &pow52) {
    return (hash[r] - hash[l] * pow52[r - l] % MOD + MOD) % MOD;
}

ll pow_(ll a, ll b) {
    ll rv = 1;
    while (b) {
        if (b & 1) {
            rv = rv * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    str s;
    cin >> s;
    ll n = sz(s), q;
    vector<ll> hash(n + 1), pow52(n + 1, 1);
    // [a,z] -> [0,25], [A,Z] -> [26,51]
    FOR (i, n) {
        pow52[i + 1] = pow52[i] * 52 % MOD;
        ll c = (s[i] >= 'a' ? s[i] - 'a' : s[i] - 'A' + 26);
        hash[i + 1] = (hash[i] * 52 + c) % MOD;
    }
    cin >> q;
    while (q--) {
        ll i, j;
        cin >> i >> j;
        ll l = 0, r = n - j;
        while (l < r) {
            ll m = (l + r + 1) / 2;
            if (get_substr(i, i + m, hash, pow52) ==
                get_substr(j, j + m, hash, pow52)) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        cout << l << '\n';
    }

    return 0;
}