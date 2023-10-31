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

const ll MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<ll> fact(2e5 + 1, 1);
    FOB (i, 1, 2e5 + 1) fact[i] = (fact[i - 1] * i) % MOD;

    ll t;
    cin >> t;
    while (t--) {
        str s;
        cin >> s;
        ll len = 1, n = sz(s);
        vector<ll> ref;
        FOB (i, 1, n) {
            if (s[i] == s[i - 1]) len++;
            else {
                ref.pb(len);
                len = 1;
            }
        }
        ref.pb(len);
        ll rv0 = 0, rv1 = 1;
        FORE (l, ref) {
            rv0 += l - 1;
            rv1 = (rv1 * l) % MOD;
        }
        rv1 = (rv1 * fact[rv0]) % MOD;
        cout << rv0 << ' ' << rv1 << '\n';
    }

    return 0;
}