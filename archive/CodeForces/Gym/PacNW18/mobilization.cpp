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

vector<pld> convex_hull(vector<pld> pts) { // returns ccw convex hull
    if (sz(pts) <= 1) return pts;
    ssort(pts);
    vector<pld> lo, hi;
    FORE (p, pts) {
        while (sz(lo) >= 2) {
            auto &p1 = lo[sz(lo) - 2], &p2 = lo[sz(lo) - 1];
            if ((p2.y - p1.y) * (p.x - p2.x) >= (p.y - p2.y) * (p2.x - p1.x)) {
                lo.pop_back();
            } else break;
        }
        lo.pb(p);
    }
    for (auto it = pts.rbegin(); it != pts.rend(); it++) {
        auto &p = *it;
        while (sz(hi) >= 2) {
            auto &p1 = hi[sz(hi) - 2], &p2 = hi[sz(hi) - 1];
            if ((p2.y - p1.y) * (p.x - p2.x) >= (p.y - p2.y) * (p2.x - p1.x)) {
                hi.pop_back();
            } else break;
        }
        hi.pb(p);
    }
    lo.pop_back(), hi.pop_back();
    lo.insert(lo.end(), hi.begin(), hi.end());
    return lo;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    map<pld, ll> idx;
    ll n, C; cin >> n >> C;
    vector<ld> c(n), h(n), p(n);
    set<pld> pts_set;
    FOR (i, n) {
        cin >> c[i] >> h[i] >> p[i];
        ld x = h[i] / c[i], y = p[i] / c[i];
        if (!idx.count({x, y})) idx[{x, y}] = i;
        elif (c[idx[{x, y}]] > c[i]) idx[{x, y}] = i;
        pts_set.insert({x, y});
    }
    vector<pld> pts(all(pts_set));
    vector<pld> hull = convex_hull(pts);
    ld ans = 0;
    ll idx0 = 0, idx1 = 1;
    do {
        pld p0 = hull[idx0], p1 = hull[idx1];
        ld tt = 0.5;
        if (p0.x != p1.x && p0.y != p1.y) 
            tt = (2 * p0.x * p0.y - p0.x * p1.y - p0.y * p1.x) / (2 * (p0.x - p1.x) * (p0.y - p1.y));
        tt = max(0.0L, min(1.0L, tt));
        for (ld t : {0.0L, tt, 1.0L}) {
            pld pt = {p0.x + t * (p1.x - p0.x), p0.y + t * (p1.y - p0.y)};
            ld cur = C * pt.x * C * pt.y;
            ans = max(ans, cur);
        }
        idx0 = idx1;
        idx1 = (idx1 + 1) % sz(hull);
    } while (idx0 != 0);
    cout << fixed << setprecision(2) << ans << '\n';

    return 0;
}