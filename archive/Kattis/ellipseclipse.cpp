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
    ll,
    null_type,
    less<ll>,
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
// #define f first
// #define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ld MAX_BOUND = 1e6;
const ld EPS = 1e-9;

// hypot(x - x1, y - y1) + hypot(x - x2, y - y2) = a
bool ok(ld x1, ld y1, ld x2, ld y2, ld a, ld x) {
    ld ylo = -MAX_BOUND, yhi = MAX_BOUND;
    while (abs(ylo - yhi) > EPS) {
        ld yy1 = (ylo * 2 + yhi) / 3, yy2 = (ylo + yhi * 2) / 3;
        ld mid1 = hypot(x - x1, yy1 - y1) + hypot(x - x2, yy1 - y2),
            mid2 = hypot(x - x1, yy2 - y1) + hypot(x - x2, yy2 - y2);
        if (mid1 < mid2) yhi = yy2;
        else ylo = yy1;
    }
    return hypot(x - x1, ylo - y1) + hypot(x - x2, ylo - y2) <= a;
}

ld find_min(ld x1, ld y1, ld x2, ld y2, ld a, ld xc, ld yc) {
    ld lo = -MAX_BOUND, hi = xc;
    while (abs(lo - hi) > EPS) {
        ld mid = (lo + hi) / 2;
        if (ok(x1, y1, x2, y2, a, mid)) hi = mid;
        else lo = mid;
    }
    return lo;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ld x1, y1, x2, y2, a;
    cin >> x1 >> y1 >> x2 >> y2 >> a;
    ld xc = (x1 + x2) / 2, yc = (y1 + y2) / 2,
        xlo = find_min(x1, y1, x2, y2, a, xc, yc),
        ylo = find_min(y1, x1, y2, x2, a, yc, xc),
        xhi = xc * 2 - xlo,
        yhi = yc * 2 - ylo;
    cout << fixed << setprecision(10) <<
        xlo << ' ' << ylo << ' ' << xhi << ' ' << yhi << '\n';

    return 0;
}