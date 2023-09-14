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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

ll count_inv(vector<ll> &a) {
    ll rv = 0;
    indexed_set s;
    FOR (i, sz(a)) {
        rv += sz(s) - s.order_of_key({a[i], -1});
        s.insert({a[i], i});
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, k, cur = 0;
    cin >> n >> k;
    set<ll> lo, hi;
    FOR (i, n) {
        lo.insert(i + 1);
    }
    while (cur + sz(lo) - 1 < k) {
        cur += sz(lo) - 1;
        hi.insert(*lo.rbegin());
        lo.erase(*lo.rbegin());
    }
    vector<ll> rv;
    FOB (it, hi.rbegin(), hi.rend()) {
        rv.pb(*it);
    }
    while (cur + sz(lo) - 1 > k) {
        rv.pb(*lo.begin());
        lo.erase(lo.begin());
    }
    rv.pb(*lo.rbegin());
    lo.erase(*lo.rbegin());
    FORE (x, lo) {
        rv.pb(x);
    }
    // assert(k == count_inv(rv));
    FORE (x, rv) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}