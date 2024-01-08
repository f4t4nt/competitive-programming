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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> a(n), b = {(ll) 1e9, 0};
        FOR (i, n) {
            cin >> a[i];
            b[0] = min(b[0], a[i]);
            b[1] = max(b[1], a[i]);
        }
        vector<ll> rv;
        while (b[0] != b[1]) {
            if (b[0] % 2 == 1 && b[1] % 2 == 0) {
                b[0] = (b[0] + 1) / 2;
                b[1] /= 2;
                rv.pb(1);
            } else {
                b[0] /= 2;
                b[1] /= 2;
                rv.pb(0);
            }
        }
        cout << sz(rv) << '\n';
        if (sz(rv) <= n) {
            FORE (x, rv) {
                cout << x << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}