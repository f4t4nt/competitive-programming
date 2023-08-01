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

#pragma GCC target("popcnt")

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, k;
    cin >> n >> k;
    vector<ll> p(k);
    FOR (i, k) {
        cin >> p[i];
    }
    ll rv = 0;
    vector<ll> prod(1 << k, 1);
    FOR (i, 1 << k) {
        FOR (j, k) {
            if (i & (1 << j)) {
                if (prod[i ^ (1 << j)] > n / p[j]) {
                    prod[i] = n + 1;
                } else {
                    prod[i] = prod[i ^ (1 << j)] * p[j];
                }
                break;
            }
        }
        ll m = __builtin_popcount(i) % 2;
        if (m == 0) {
            rv += n / prod[i];
        } else {
            rv -= n / prod[i];
        }
    }
    rv = n - rv;
    cout << rv << '\n';

    return 0;
}