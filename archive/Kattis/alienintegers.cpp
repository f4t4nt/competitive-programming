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

ll get_mn(str &n0s, set<ll> &a) {
    ll mx = *a.rbegin();
    str rv = str(sz(n0s), '0' + mx);
    bool ok = false;
    FORE (d, a) {
        if ('0' + d < n0s[0]) {
            ok = true;
            rv[0] = '0' + d;
        }
    }
    if (!ok) {
        if (sz(rv) > 1) {
            rv = rv.substr(1);
        }
    }
    return stoll(rv);
}

ll get_mx(str &n0s, set<ll> &a) {
    ll mn = *a.begin();
    str rv = str(sz(n0s), '0' + mn);
    bool ok = false;
    FORE (d, a) {
        if ('0' + d > n0s[0]) {
            rv[0] = '0' + d;
            ok = true;
            break;
        }
    }
    if (!ok) {
        if (mn == 0) {
            if (sz(a) == 1) {
                return 1e18;
            }
            mn = *next(a.begin());
        }
        rv = str(1, '0' + mn) + rv;
    }
    return stoll(rv);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    str n0s;
    cin >> n0s;
    ll n0 = stoll(n0s), n = n0;
    vector<bool> used(10);
    while (n) {
        used[n % 10] = true;
        n /= 10;
    }
    set<ll> a;
    FOR (i, 10) {
        if (!used[i]) {
            a.insert(i);
        }
    }
    if (a.empty()) {
        cout << "Impossible\n";
        return 0;
    }
    ll rv0 = get_mn(n0s, a), rv1 = get_mx(n0s, a);
    if (abs(n0 - rv0) < abs(n0 - rv1)) {
        cout << rv0 << '\n';
    } elif (abs(n0 - rv0) > abs(n0 - rv1)) {
        cout << rv1 << '\n';
    } else {
        cout << rv0 << ' ' << rv1 << '\n';
    }

    return 0;
}