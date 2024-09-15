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
#define f first
#define s second

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

const ll RES = 100;
const ld EPS = 1e-12;
ld DEL = 0.01;

ld pt_to_pt(pld p0, pld p1) {
    ld dx = p0.f - p1.f, dy = p0.s - p1.s;
    return sqrt(dx * dx + dy * dy);
}

struct Pyramid {
    ld x[4], y[4], h;
    pld pk;

    void init() {
        ll dx = x[1] - x[0], dy = y[1] - y[0];
        x[2] = x[1] - dy, y[2] = y[1] + dx;
        x[3] = x[0] - dy, y[3] = y[0] + dx;
        pk = {(x[0] + x[2]) / 2, (y[0] + y[2]) / 2};
    }

    pld k_to_pt(ld k) {
        while (k < 0) k++;
        while (k >= 1) k--;
        k *= 4;
        ll k0 = k, k1 = (k0 + 1) % 4;
        k -= k0;
        pld res = {x[k0] + (x[k1] - x[k0]) * k, y[k0] + (y[k1] - y[k0]) * k};
        return res;
    }

    ld pk_to_pt(pld pt) {
        ld dx = pt.f - pk.f, dy = pt.s - pk.s;
        return sqrt(dx * dx + dy * dy + h * h);
    }
};

Pyramid p0, p1;

ld eval(ld k0, ld k1) {
    pld pt0 = p0.k_to_pt(k0), pt1 = p1.k_to_pt(k1);
    return pt_to_pt(pt0, pt1) + p0.pk_to_pt(pt0) + p1.pk_to_pt(pt1);
}

tuple<ld, ld, ld> get_best_k() {
    tuple<ld, ld, ld> best = {1e18, -1, -1};
    FOR (i, RES) FOR (j, RES) {
        ld k0 = (ld)i / RES, k1 = (ld)j / RES;
        pld pt0 = p0.k_to_pt(k0), pt1 = p1.k_to_pt(k1);
        ld d = eval(k0, k1);
        best = min(best, {d, k0, k1});
    }
    return best;
}

ld ans = 1e18;

pld ternary_search_k1(ld k0, ld k1) {
    ld lo = k1 - DEL, hi = k1 + DEL, cur = 1e18;
    while (abs(hi - lo) > EPS) {
        ld mid0 = (3 * lo + hi) / 4, mid1 = (lo + 3 * hi) / 4;
        ld d0 = eval(k0, mid0), d1 = eval(k0, mid1);
        cur = min({cur, d0, d1});
        ans = min(ans, cur);
        if (d0 < d1) hi = mid1;
        else lo = mid0;
    }
    return {cur, lo};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> p0.x[0] >> p0.y[0] >> p0.x[1] >> p0.y[1] >> p0.h;
    cin >> p1.x[0] >> p1.y[0] >> p1.x[1] >> p1.y[1] >> p1.h;
    p0.init(), p1.init();

    auto [d, k0, k1] = get_best_k();
    ans = d;

    FOR (_, 15) {
        ld lo = k0 - DEL, hi = k0 + DEL;
        while (abs(hi - lo) > EPS) {
            ld mid0 = (3 * lo + hi) / 4, mid1 = (lo + 3 * hi) / 4;
            ld d0 = ternary_search_k1(mid0, k1).f,
                d1 = ternary_search_k1(mid1, k1).f;
            if (d0 < d1) hi = mid1;
            else lo = mid0;
        }
        k0 = (lo + hi) / 2;
        tie(d, k1) = ternary_search_k1(k0, k1);
        ans = min(ans, d);
    }

    cout << fixed << setprecision(10) << ans << '\n';

    return 0;
}