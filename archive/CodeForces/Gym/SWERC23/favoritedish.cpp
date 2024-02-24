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

vector<pll> convex_hull(vector<pll> pts) {
    if (sz(pts) <= 1) return pts;
    ssort(pts);
    vector<pll> lo, hi;
    FORE (p, pts) {
        while (sz(lo) >= 2) {
            auto &p1 = lo[sz(lo) - 2], &p2 = lo[sz(lo) - 1];
            if ((p2.y - p1.y) * (p.x - p2.x) > (p.y - p2.y) * (p2.x - p1.x)) {
                lo.pop_back();
            } else break;
        }
        lo.pb(p);
    }
    for (auto it = pts.rbegin(); it != pts.rend(); it++) {
        auto &p = *it;
        while (sz(hi) >= 2) {
            auto &p1 = hi[sz(hi) - 2], &p2 = hi[sz(hi) - 1];
            if ((p2.y - p1.y) * (p.x - p2.x) > (p.y - p2.y) * (p2.x - p1.x)) {
                hi.pop_back();
            } else break;
        }
        hi.pb(p);
    }
    lo.pop_back(), hi.pop_back();
    lo.insert(lo.end(), hi.begin(), hi.end());
    return lo;
}

ll eval(pll pt, pll line) {
    return pt.x * line.x + pt.y * line.y;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
 
    ll n, m; cin >> n >> m;
    pll pt0 = {0, 0}, pt1 = {0, 0};
    vector<pll> pts(n), lines(m);
    map<pll, ll> pts_id, lines_id;
    FOR (i, n) {
        cin >> pts[i].x >> pts[i].y;
        pts_id[pts[i]] = i + 1;
        if (pts[i].y > pt0.y) pt0 = pts[i];
        elif (pts[i].y == pt0.y && pts[i].x < pt0.x) pt0 = pts[i];
        if (pts[i].x > pt1.x) pt1 = pts[i];
        elif (pts[i].x == pt1.x && pts[i].y < pt1.y) pt1 = pts[i];
    }
    FOR (i, m) {
        cin >> lines[i].x >> lines[i].y;
        lines_id[lines[i]] = i;
    }
    vector<pll> hull = convex_hull(pts);
    sort(all(lines), [](pll a, pll b) {
        return a.x * b.y > a.y * b.x;
    });
    ll idx = 0;
    FOR (i, sz(hull)) {
        if (hull[i] == pt1) {
            idx = i;
            break;
        }
    }
    vector<ll> ans(m);
    pll best_pt = hull[idx], pt = hull[idx];
    ll best_idx = idx, best_val = -1, best_id = pts_id[best_pt], val, id;
    FOR (i, m) {
        pll line = lines[i];
        best_val = eval(best_pt, line);
        val = eval(pt, line);
        if (val > best_val) {
            best_val = val;
            best_idx = idx;
            best_id = pts_id[pt];
            best_pt = pt;
        }
        while (true) {
            idx = (idx + 1) % sz(hull),
                pt = hull[idx],
                val = eval(pt, line),
                id = pts_id[pt];
            if (val > best_val) {
                best_val = val;
                best_idx = idx;
                best_id = id;
                best_pt = pt;
            } elif (val == best_val) {
                if (id < best_id) {
                    best_id = id;
                    best_pt = pt;
                    best_idx = idx;
                }
            } else break;
            if (pt == pt0) break;
        }
        idx = (idx - 1 + sz(hull)) % sz(hull),
            pt = hull[idx],
            val = eval(pt, line),
            id = pts_id[pt];
        ans[lines_id[line]] = best_id;
    }
    // FOR (i, m) {
    //     pll line = lines[i];
    //     ll best_val = -1, best_id = 1e18, cur = idx;
    //     while (true) {
    //         ll val = eval(hull[cur], line);
    //         if (val > best_val) {
    //             best_val = val;
    //             best_id = pts_id[hull[cur]];
    //         } elif (val == best_val) {
    //             best_id = min(best_id, pts_id[hull[cur]]);
    //         } else break;
    //         if (hull[cur] == pt0) break;
    //         cur = (cur + 1) % sz(hull);
    //     }
    //     ans[lines_id[line]] = best_id;
    // }
    FORE (i, ans) cout << i << '\n';

    return 0;
}