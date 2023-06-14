#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

pair<ld, ld> get_com(vector<pair<ld, ld>> &poly) {
    ld x = 0, y = 0;
    ld area = 0;
    FOR (i, sz(poly)) {
        ll j = (i + 1) % sz(poly);
        ld a = poly[i].first * poly[j].second - poly[j].first * poly[i].second;
        area += a;
        x += (poly[i].first + poly[j].first) * a;
        y += (poly[i].second + poly[j].second) * a;
    }
    area /= 2;
    x /= 6 * area;
    y /= 6 * area;
    return {x, y};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ld n, w, v, theta, x_lim;
    cin >> n >> w >> v >> theta >> x_lim;
    theta *= M_PI / 180;
    v *= cos(theta);
    w *= -1;
    vector<pair<ld, ld>> poly(n);
    FOR (i, n) {
        cin >> poly[i].first >> poly[i].second;
    }
    pair<ld, ld> com = get_com(poly);
    vector<ld> dists(n), angles(n);
    ld min_dist = 1e18, max_dist = 0;
    FOR (i, n) {
        dists[i] = sqrt(pow(poly[i].first - com.first, 2) + pow(poly[i].second - com.second, 2));
        angles[i] = atan2(poly[i].second - com.second, poly[i].first - com.first);
        min_dist = min(min_dist, dists[i]);
        max_dist = max(max_dist, dists[i]);
    }
    vector<pair<ld, ld>> poly_norm(n);
    FOR (i, n) {
        poly_norm[i] = {poly[i].first - com.first, poly[i].second - com.second};
    }
    ld t_lo = max((x_lim - com.first - max_dist) / v, (ld) 0),
        t_hi = (x_lim - com.first - min_dist) / v + 1;
    vector<ld> times(n, 1e18);
    pair<ld, ll> rv = {t_hi, -1};
    FOR (i, n) {
        if (v >= dists[i] * -w && com.first + v * rv.first + dists[i] * cos(angles[i] + w * rv.first) >= x_lim) {
            ld lo = t_lo, hi = rv.first;
            while (hi - lo > 1e-6) {
                ld mid = (lo + hi) / 2;
                ld x = com.first + v * mid + dists[i] * cos(angles[i] + w * mid);
                if (x >= x_lim) {
                    hi = mid;
                } else {
                    lo = mid;
                }
            }
            times[i] = lo;
        } else {
            for (ld t = t_lo; t <= rv.first; t += 1e-3 - 1e-6) {
                ld x = com.first + v * t + dists[i] * cos(angles[i] + w * t);
                if (x >= x_lim) {
                    times[i] = min(times[i], t);
                    break;
                }
            }
        }
        rv = min(rv, {times[i], i});
    }
    // FOR (i, n) {
    //     rv = min(rv, {times[i], i});
    // }
    assert(rv.second != -1);
    cout << rv.second + 1 << ' ' << fixed << setprecision(10) << rv.first << '\n';

    return 0;
}