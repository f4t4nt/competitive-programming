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

ll a, b, c, k;
const ll MAXK = 10001;
bitset<MAXK> one;
map<ll, set<ll>> memf0;
map<ll, bitset<MAXK>> memf1;
map<ll, pair<ll, ll>> memg;

set<ll> f0(ll i) {
    if (memf0.count(i)) {
        return memf0[i];
    }
    if (i <= 0) {
        return memf0[i] = {1};
    }
    set<ll> rv;
    FOR (j, c) {
        auto s = f0(i - j - 1);
        FORE (x, s) {
            FOB (y, a, a + b) {
                if (x + y > k) {
                    break;
                }
                rv.insert(x + y);
            }
        }
    }
    // ll l = *rv.begin(), r = *rv.rbegin();
    // assert(sz(rv) == r - l + 1);
    return memf0[i] = rv;
}

bitset<MAXK> f1(ll i) {
    if (memf1.count(i)) {
        return memf1[i];
    }
    if (i <= 0) {
        return memf1[i] = one;
    }
    bitset<MAXK> rv;
    FOR (j, c) {
        auto s = f1(i - j - 1);
        FOB (y, a, a + b) {
            rv |= (s << y);
        }
    }
    return memf1[i] = rv;
}

pair<ll, ll> g(ll i) {
    if (memg.count(i)) {
        return memg[i];
    }
    if (i <= 0) {
        return memg[i] = {1, 1};
    }
    pair<ll, ll> rv = {1e18, -1e18};
    FOR (j, c) {
        auto [l, r] = g(i - j - 1);
        rv.first = min(rv.first, l + a);
        rv.second = max(rv.second, r + a + b - 1);
    }
    return memg[i] = rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    one[1] = 1;

    ll i;
    while (cin >> a >> b >> c >> i >> k) {
        memf0.clear();
        memf1.clear();
        memg.clear();
        // auto s0 = f0(i);
        auto s1 = f1(i);
        // cout << ((s0.count(k)) ? "possible" : "impossible") << '\n';
        cout << ((s1[k]) ? "possible" : "impossible") << '\n';
        // auto [l, r] = g(i);
        // cout << ((l <= k && k <= r) ? "possible" : "impossible") << '\n';
    }

    return 0;
}