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

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<pair<ll, ll>> a(n);
        FOR (i, n) {
            cin >> a[i].first;
            a[i].second = i;
        }
        ssort(a);
        bool ok = true;
        vector<ll> rv(n);
        ll l = 0, r = n - 1, cur = n;
        while (l <= r) {
            if ((a[r].first == n - l) ^ (a[l].first == n - 1 - r)) {
                if (a[r].first == n - l) {
                    rv[a[r].second] = cur;
                    r--, cur--;
                } else {
                    rv[a[l].second] = -cur;
                    l++, cur--;
                }
            } else {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << "YES\n";
            FORE (x, rv) {
                cout << x << ' ';
            }
            cout << '\n';
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}