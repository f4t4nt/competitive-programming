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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n, cnt_pos = 0, cnt_neg = 0;
        pair<ll, ll> max_a = {-1e18, -1}, min_a = {1e18, -1};
        cin >> n;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
            cnt_pos += (a[i] > 0);
            cnt_neg += (a[i] < 0);
            if (a[i] > max_a.first) {
                max_a = {a[i], i};
            }
            if (a[i] < min_a.first) {
                min_a = {a[i], i};
            }
        }
        vector<pair<ll, ll>> rv;
        if (cnt_pos >= cnt_neg) {
            ll k = max_a.second;
            while (a[k] < -min_a.first) {
                rv.pb({k, k});
                a[k] += a[k];
            }
            ll i = 0;
            FOR (i, n) {
                if (a[i] < 0) {
                    rv.pb({i, k});
                    a[i] += a[k];
                }
            }
            FOB (i, 1, n) {
                if (a[i - 1] > a[i]) {
                    rv.pb({i, i - 1});
                    a[i] += a[i - 1];
                }
            }
        } else {
            ll k = min_a.second;
            while (a[k] > -max_a.first) {
                rv.pb({k, k});
                a[k] += a[k];
            }
            ll i = 0;
            FOR (i, n) {
                if (a[i] > 0) {
                    rv.pb({i, k});
                    a[i] += a[k];
                }
            }
            for (ll i = n - 1; i > 0; i--) {
                if (a[i - 1] > a[i]) {
                    rv.pb({i - 1, i});
                    a[i - 1] += a[i];
                }
            }
        }
        // assert(is_sorted(all(a)));
        // assert(sz(rv) <= 31);
        cout << sz(rv) << '\n';
        FORE (x, rv) {
            cout << x.first + 1 << ' ' << x.second + 1 << '\n';
        }
    }

    return 0;
}