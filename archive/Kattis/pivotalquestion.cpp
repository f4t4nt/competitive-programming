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

// imma show YOU how great i am.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> a(n);
    set<ll> lo, hi;
    FOR (i, n) {
        cin >> a[i];
        hi.insert(a[i]);
    }
    vector<ll> rv;
    FOR (i, n) {
        hi.erase(a[i]);
        bool ok_lo = true, ok_hi = true;
        if (sz(lo) > 0) {
            ok_lo = *lo.rbegin() <= a[i];
        }
        if (sz(hi) > 0) {
            ok_hi = *hi.begin() > a[i];
        }
        if (ok_lo && ok_hi) {
            rv.pb(a[i]);
        }
        lo.insert(a[i]);
    }
    cout << sz(rv) << ' ';
    FOR (i, min(100LL, sz(rv))) {
        cout << rv[i] << ' ';
    }
    cout << '\n';

    return 0;
}