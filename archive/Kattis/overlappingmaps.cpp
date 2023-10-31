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

const ld EPS = 1e-6;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ld w, h, x, y, s, r;
    while (cin >> w >> h >> x >> y >> s >> r && w) {
        ld x0 = w / 2, y0 = h / 2, x1, y1;
        s /= 100;
        r = r * M_PI / 180;
        do {
            x1 = x0, y1 = y0;
            ld rho = s * sqrt(x0 * x0 + y0 * y0),
                ang = atan2(y0, x0) + r;
            x0 = x + rho * cos(ang);
            y0 = y + rho * sin(ang);
        } while (abs(x0 - x1) > EPS || abs(y0 - y1) > EPS);
        cout << fixed << setprecision(2) << x0 << ' ' << y0 << '\n';
    }

    return 0;
}