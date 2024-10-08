#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
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

ll pow_mod(ll a, ll b) {
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

    ll n;
    cin >> n;
    // (2 ^ (n ^ 2) +
    //  2 * 2 ^ ((n ^ 2 + 3 * (n % 2)) / 4)
    //  + 2 ^ ((n ^ 2 + n % 2) / 2)
    // ) / 4
    ll rv = ((pow_mod(2, n * n) +
             2 * pow_mod(2, (n * n + 3 * (n % 2)) / 4) +
             pow_mod(2, (n * n + n % 2) / 2)) % MOD) * pow_mod(4, MOD - 2) % MOD;
    cout << rv << '\n';

    return 0;
}