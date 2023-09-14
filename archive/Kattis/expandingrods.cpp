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
    cin.tie(0);
    cout.tie(0);

    ld l0, n, c;
    while (cin >> l0 >> n >> c) {
        if (l0 == -1 && n == -1 && c == -1) {
            break;
        }
        l0 /= 2;
        ld x = 1 + n * c, lo = 0, hi = M_PI / 2;
        if (x == 1) {
            cout << 0 << '\n';
            continue;
        }
        while (hi - lo > 1e-15) {
            ld mid = (lo + hi) / 2;
            if (mid / sin(mid) < x) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        cout << fixed << setprecision(6) << l0 / sin(lo) * (1 - cos(lo)) << '\n';
    }

    return 0;
}