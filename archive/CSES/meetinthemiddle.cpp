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

    ll n, x;
    cin >> n >> x;
    vector<ll> a(n);
    FOR (i, n) {
        cin >> a[i];
    }
    ll n0 = n / 2;
    n -= n0;
    ssort(a);
    vector<ll> dp0(1 << n), dp1(1 << n0);
    unordered_map<ll, ll> cnts;
    FOR (i, 1 << n) {
        FOR (j, n) {
            if (i & (1 << j)) {
                dp0[i] = dp0[i ^ (1 << j)] + a[j];
                break;
            }
        }
        cnts[dp0[i]]++;
    }
    ll rv = 0;
    FOR (i, 1 << n0) {
        FOR (j, n0) {
            if (i & (1 << j)) {
                dp1[i] = dp1[i ^ (1 << j)] + a[j + n];
                break;
            }
        }
        if (cnts.count(x - dp1[i])) {
            rv += cnts[x - dp1[i]];
        }
    }
    cout << rv << '\n';

    return 0;
}