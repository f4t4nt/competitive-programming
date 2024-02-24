#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define x first
#define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

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
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ld x1, y1, x2, y2, xg, yg; cin >> xg >> yg >> x1 >> y1 >> x2 >> y2;
    x1 -= xg, x2 -= xg, y1 -= yg, y2 -= yg;
    xg = 0, yg = 0;
    ld r = 1e6;
    if (x1 <= 0 && x2 >= 0 && y1 >= 0) r = min(r, y1);
    if (x1 <= 0 && x2 >= 0 && y2 <= 0) r = min(r, -y2);
    if (y1 <= 0 && y2 >= 0 && x1 >= 0) r = min(r, x1);
    if (y1 <= 0 && y2 >= 0 && x2 <= 0) r = min(r, -x2);
    r = min({r, hypot(x1, y1), hypot(x1, y2), hypot(x2, y1), hypot(x2, y2)});
    cout << fixed << setprecision(3) << r << '\n';

    return 0;
}