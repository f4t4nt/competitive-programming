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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
        }
        ssort(a);
        if (a[0] == a.back()) {
            cout << -1 << '\n';
            continue;
        }
        vector<ll> rv0, rv1;
        FOR (i, n) {
            if (a[i] != a.back()) {
                rv0.pb(a[i]);
            } else {
                rv1.pb(a[i]);
            }
        }
        cout << sz(rv0) << ' ' << sz(rv1) << '\n';
        FORE (x, rv0) {
            cout << x << ' ';
        }
        cout << '\n';
        FORE (x, rv1) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}