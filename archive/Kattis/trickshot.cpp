#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
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

#define x first
#define y second

pair<ld, ld> extend(pair<ld, ld> p0, pair<ld, ld> p1, ld r) {
    ld dx = p1.x - p0.x, dy = p1.y - p0.y;
    ld d = sqrt(dx * dx + dy * dy);
    dx /= d, dy /= d;
    return {p1.x + dx * r, p1.y + dy * r};
}

// angle between vec p0p1 and p0p2
ld angle(pair<ld, ld> p0, pair<ld, ld> p1, pair<ld, ld> p2) {
    pair<ld, ld> w = {p1.x - p0.x, p1.y - p0.y},
        v = {p2.x - p0.x, p2.y - p0.y};
    return atan2(
        w.y * v.x - w.x * v.y,
        w.x * v.x + w.y * v.y
    );
}

// proj p2 onto p0p1
pair<ld, ld> proj(pair<ld, ld> p0, pair<ld, ld> p1, pair<ld, ld> p2) {
    pair<ld, ld> w = {p1.x - p0.x, p1.y - p0.y},
        v = {p2.x - p0.x, p2.y - p0.y};
    ld d = sqrt(w.x * w.x + w.y * w.y);
    w.x /= d, w.y /= d;
    return {p0.x + w.x * (w.x * v.x + w.y * v.y), p0.y + w.y * (w.x * v.x + w.y * v.y)};
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ld w, l, r, h; cin >> w >> l >> r;
    pair<ld, ld> holel = {0, l}, holer = {w, l}, p1, p2, p3;
    cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> h;
    // if (p1.y > p2.y || p1.y > p3.y) {
    //     cout << "impossible\n";
    //     return 0;
    // }
    pair<ld, ld> pc2 = extend(holel, p2, 2 * r),
        p13 = extend(holer, p3, 2 * r),
        pc1 = extend(p13, p1, 2 * r);
    ld ang1 = angle(pc1, pc2, p13) * 180 / M_PI;
    if (ang1 <= 90) {
        cout << "impossible\n";
        return 0;
    }
    pair<ld, ld> projc = proj(pc1, p13, pc2),
        pcr = {projc.x * 2 - pc2.x, projc.y * 2 - pc2.y};
    ld dx = pcr.x - pc1.x, dy = pcr.y - pc1.y, dy1 = h - pc1.y;
    pair<ld, ld> pc0 = {pc1.x + dx * dy1 / dy, h};
    if (pc0.x < r || pc0.x > w - r) {
        cout << "impossible\n";
        return 0;
    }
    ld ang0 = angle(pc0, pc1, {1e3, h}) * 180 / M_PI;
    pair<ld, ld> proj2c = proj(pc0, p1, p2),
        proj3c = proj(pc0, p1, p3);
    if (hypot(proj2c.x - p2.x, proj2c.y - p2.y) < r ||
        hypot(proj3c.x - p3.x, proj3c.y - p3.y) < r) {
        cout << "impossible\n";
        return 0;
    }
    cout << fixed << setprecision(2) << pc0.x << ' ' << ang0 << '\n';

    return 0;
}