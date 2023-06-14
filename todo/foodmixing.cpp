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

// https://codesprintla23.kattis.com/problems/codesprintla23.foodmixing

vector<pair<ld, ld>> convex_hull(vector<pair<ld, ld>> points) {
    // sort points by x-coordinate
    ssort(points);

    // lower hull
    vector<pair<ld, ld>> lower;
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
    vector<pair<ld, ld>> upper;
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

bool in_triangle(pair<ld, ld> &point, vector<pair<ld, ld>> &triangle) {
    vector<ld> d(3);
    FOR (i, 3) {
        auto &p1 = triangle[i];
        auto &p2 = triangle[(i + 1) % 3];
        d[i] = (p2.first - p1.first) * (point.second - p1.second) -
            (p2.second - p1.second) * (point.first - p1.first);
    }
    return (d[0] >= 0 && d[1] >= 0 && d[2] >= 0) || (d[0] <= 0 && d[1] <= 0 && d[2] <= 0);
}

ll get_triangle(
    vector<pair<ld, ld>> &points,
    vector<pair<ld, ld>> &triangle,
    pair<ld, ld> &target
) {
    triangle[0] = points[0];
    FOB (i, 1, sz(points) - 1) {
        triangle[1] = points[i];
        triangle[2] = points[i + 1];
        if (in_triangle(target, triangle)) {
            return i;
        }
    }
    return -1;
}

ld area_triangle(vector<pair<ld, ld>> triangle) {
    ld area = 0;
    FOR (i, 3) {
        auto &p1 = triangle[i];
        auto &p2 = triangle[(i + 1) % 3];
        area += p1.first * p2.second - p2.first * p1.second;
    }
    return abs(area) / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<pair<ld, ld>> points(n);
    FOR (i, n) {
        cin >> points[i].first;
    }
    FOR (i, n) {
        cin >> points[i].second;
    }
    if (sz(points) < 3) {
        points.pb({points[n - 1].first + 1e-6, points[n - 1].second + 1e-9});
    }
    if (sz(points) < 3) {
        points.pb({points[n - 1].first + 1e-9, points[n - 1].second + 1e-6});
    }
    pair<ld, ld> target;
    cin >> target.first >> target.second;
    auto hull = convex_hull(points);
    vector<pair<ld, ld>> triangle(3);
    ll i = get_triangle(hull, triangle, target);
    if (i == -1) {
        cout << "No\n";
        return 0;
    }
    vector<ll> idxs = {
        find(all(points), triangle[0]) - points.begin(),
        find(all(points), triangle[1]) - points.begin(),
        find(all(points), triangle[2]) - points.begin()
    };
    ld total = area_triangle(triangle);
    vector<ld> ref = {
        area_triangle({target, triangle[1], triangle[2]}) / total,
        area_triangle({target, triangle[0], triangle[2]}) / total,
        area_triangle({target, triangle[0], triangle[1]}) / total
    };
    vector<ld> rv(n);
    ld sum = 0;
    FOR (i, 3) {
        if (idxs[i] >= 0 && idxs[i] < n) {
            rv[idxs[i]] = ref[i];
            sum += ref[i];
        }
    }
    if (sum != 1) {
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    FOR (i, n) {
        cout << fixed << setprecision(10) << rv[i] << ' ';
    }
    cout << '\n';

    return 0;
}