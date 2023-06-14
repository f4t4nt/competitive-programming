#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

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

vector<pair<ll, ll>> convex_hull(vector<pair<ll, ll>> points) {
    // sort points by x-coordinate
    ssort(points);

    // lower hull
    vector<pair<ll, ll>> lower;
    for (auto &p : points) {
        while (sz(lower) >= 2) {
            auto &p1 = lower[sz(lower) - 2];
            auto &p2 = lower[sz(lower) - 1];
            if ((p2.second - p1.second) * (p.first - p2.first) >= (p.second - p2.second) * (p2.first - p1.first)) {
                lower.pop_back();
            } else {
                break;
            }
        }
        lower.pb(p);
    }

    // upper hull
    vector<pair<ll, ll>> upper;
    for (auto it = points.rbegin(); it != points.rend(); it++) {
        auto &p = *it;
        while (sz(upper) >= 2) {
            auto &p1 = upper[sz(upper) - 2];
            auto &p2 = upper[sz(upper) - 1];
            if ((p2.second - p1.second) * (p.first - p2.first) >= (p.second - p2.second) * (p2.first - p1.first)) {
                upper.pop_back();
            } else {
                break;
            }
        }
        upper.pb(p);
    }

    // remove duplicates
    lower.pop_back();
    upper.pop_back();

    // merge lower and upper hulls
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

bool in_triangle(pair<ll, ll> &point, vector<pair<ll, ll>> &tri) {
    vector<ld> d(3);
    FOR (i, 3) {
        auto &p1 = tri[i];
        auto &p2 = tri[(i + 1) % 3];
        d[i] = (p2.first - p1.first) * (point.second - p1.second) -
            (p2.second - p1.second) * (point.first - p1.first);
    }
    return (d[0] >= 0 && d[1] >= 0 && d[2] >= 0) || (d[0] <= 0 && d[1] <= 0 && d[2] <= 0);
}

ll get_triangle(
    vector<pair<ll, ll>> &points,
    vector<pair<ll, ll>> &tri,
    pair<ll, ll> &target
) {
    ll idx = rand() % sz(points);
    tri[0] = points[idx];
    FOR (i, sz(points)) {
        if (i == idx) {
            continue;
        }
        tri[1] = points[i];
        tri[2] = points[(i + 1) % sz(points)];
        if (in_triangle(target, tri)) {
            return i;
        }
    }
    return -1;
}

ld area_triangle(vector<pair<ll, ll>> tri) {
    ld area = 0;
    FOR (i, 3) {
        auto &p1 = tri[i];
        auto &p2 = tri[(i + 1) % 3];
        area += p1.first * p2.second - p2.first * p1.second;
    }
    return abs(area);
}

ld dist_(pair<ld, ld> a, pair<ld, ld> b) {
    return sqrt((a.first - b.first) * (a.first - b.first) +
        (a.second - b.second) * (a.second - b.second));
}

ld dist(pair<ll, ll> a, pair<ld, ld> b) {
    return dist_({(ld) a.first, (ld) a.second}, b);
}

ld dist(pair<ll, ll> a, pair<ll, ll> b) {
    return dist_({(ld) a.first, (ld) a.second}, {(ld) b.first, (ld) b.second});
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<pair<ll, ll>> pts(n), pts_trunc;
    map<pair<ll, ll>, ld> ref;
    FOR (i, n) {
        cin >> pts[i].first;
    }
    FOR (i, n) {
        cin >> pts[i].second;
    }
    FORE (p, pts) {
        ref[p] = 0;
    }
    FORE (e, ref) {
        pts_trunc.pb(e.first);
    }
    pair<ll, ll> target;
    cin >> target.first >> target.second;
    if (sz(pts_trunc) == 1) {
        if (pts_trunc[0] == target) {
            ref[pts_trunc[0]] = 1;
        }
    } else {
        auto hull = convex_hull(pts_trunc);
        if (sz(hull) == 2) {
            if (hull[0].first != hull[1].first) {
                ref[hull[0]] = (target.first - hull[1].first) / (ld) (hull[0].first - hull[1].first);
            } else {
                ref[hull[0]] = (target.second - hull[1].second) / (ld) (hull[0].second - hull[1].second);
            }
            ref[hull[1]] = 1 - ref[hull[0]];
        } else {
            ll best_i = -1;
            ld best_area = 0;
            vector<pair<ll, ll>> best_tri;
            FOR (rep, 3000) {
                vector<pair<ll, ll>> tri(3);
                ll i = get_triangle(hull, tri, target);
                ld area = area_triangle(tri);
                if (i != -1 && area > best_area) {
                    best_i = i;
                    best_area = area;
                    best_tri = tri;
                }
            }
            if (best_i != -1) {
                ref[best_tri[0]] = area_triangle({target, best_tri[1], best_tri[2]});
                ref[best_tri[1]] = area_triangle({target, best_tri[0], best_tri[2]});
                ref[best_tri[2]] = area_triangle({target, best_tri[0], best_tri[1]});
            }
        }
    }

    ld sum = 0;
    pair<ld, ld> tmp = {0,0};
    vector<ld> rv(n);
    FOR (i, n) {
        rv[i] = ref[pts[i]];
        sum += ref[pts[i]];
        ref[pts[i]] = 0;
    }
    if (sum == 0) {
        cout << "No\n";
        return 0;
    }
    FOR (i, n) {
        rv[i] /= sum;
        tmp.first += rv[i] * pts[i].first;
        tmp.second += rv[i] * pts[i].second;
    }
    if (dist(target, tmp) > 2e-6) {
        cout << "No\n";
        return 0;
    }

    cout << "Yes\n";
    FORE (x, rv) {
        cout << fixed << setprecision(10) << x << ' ';
    }
    cout << '\n';

    return 0;
}