#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
// s.order_of_key(x) -> number of elements < x
// s.find_by_order(x) -> iterator to the x-th element (0-indexed)

#pragma GCC target("popcnt,lzcnt")
// __builtin_popcount(x) -> number of set bits
// __builtin_clz(x) -> number of leading zeros
// for ll, use __builtin_popcountll, __builtin_clzll

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define x first
// #define y second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll INF = 4e18;

struct Line {
    ll m, b;        // y = mx + b
    ld x_left;      // intersection with previous line
    Line(ll _m = 0, ll _b = INF) : m(_m), b(_b), x_left(-1e18) {}
    // evaluate at integer x
    inline ll val(ll x) const { return m * x + b; }
    // intersection point (as double) with other line
    static ld isect(const Line &p, const Line &q) {
        // assumes p.m < q.m
        return (ld) (q.b - p.b) / (p.m - q.m);
    }
};

// -----------------------------------------------------------------------------
//  Convex Hull Trick
// -----------------------------------------------------------------------------
//  Supports:   - add_line(m, b)   insert y = m x + b
//              - query(x)         minimum y at x for all lines
//  Restrictions:
//              - Lines MUST be added in strictly monotone order of slope
//                (increasing for a lower hull / min queries).
//              - Query points x MUST be non-decreasing.
//                (If queries are arbitrary, use binary-search version below.)
//  Complexity:  O(1) amortised per operation with the above monotone guarantees
//               Memory   O(# of lines)
//  Notes:      - Works with 64-bit integers as long as no overflow occurs in
//                m * x + b.  For safer usage with large coordinates, switch
//                to long double.
//              - swap max/min by flipping sign of m and b (or by inverting
//                inequality in isect()).
// -----------------------------------------------------------------------------
struct ConvexHullTrick {
    deque<Line> hull;   // lower hull (for min queries)

    // insert line with strictly higher slope than last inserted
    void add_line(Line nw) {
        // remove last line if it's useless
        while (sz(hull) >= 1) {
            ld x = Line::isect(hull.back(), nw);
            if (x <= hull.back().x_left) hull.pop_back();
            else { nw.x_left = x; break; }
        }
        if (hull.empty()) nw.x_left = -1e18;
        hull.pb(nw);
    }

    void add_line(ll m, ll b) {
        add_line(Line(m, b));
    }

    // min y at query point x (x must be non-decreasing across calls)
    ll query(ll x) {
        assert(!hull.empty());
        while (sz(hull) >= 2 && hull[1].x_left <= x) hull.pop_front();
        return hull.front().val(x);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, k; cin >> n >> k;
    vector<ll> a(n + 1), pre(n + 1);
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }
    vector<ll> dp0(n + 1, INF), dp1(n + 1, INF);
    dp0[0] = 0;
    for (ll seg = 1; seg <= k; seg++) {
        ConvexHullTrick cht;
        dp1.assign(n + 1, INF);
        for (ll i = seg; i <= n; i++) {
            ll j = i - 1;
            if (dp0[j] < INF) {
                ll m = -2 * pre[j];
                ll b = dp0[j] + pre[j] * pre[j];
                cht.add_line(m, b);
            }
            dp1[i] = pre[i] * pre[i] + cht.query(pre[i]);
        }
        swap(dp0, dp1);
    }
    cout << dp0[n] << '\n';

    return 0;
}