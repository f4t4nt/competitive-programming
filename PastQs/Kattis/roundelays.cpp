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

vector<pair<ld, ld>> convex_hull(vector<pair<ld, ld>> points) {
    if (sz(points) == 0) {
        return {};
    }

    // sort points by x-coordinate
    // ssort(points);

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<pair<ld, ld>> pts(n);
    FOR (i, n) {
        cin >> pts[i].first >> pts[i].second;
    }
    ssort(pts);

    ll rv = 1e18;
    FOR (i, n) {
        FOB (j, i + 1, n) {
            pair<ld, ld> &pi = pts[i], &pj = pts[j];
            vector<pair<ld, ld>> side0, side1;
            FORE (p, pts) {
                if (p == pi) {
                    side0.pb(pi);
                    continue;
                } elif (p == pj) {
                    side1.pb(pj);
                    continue;
                }
                ld val = (pj.first - pi.first) * (p.second - pi.second) -
                    (pj.second - pi.second) * (p.first - pi.first);
                if (val > 0) {
                    side0.pb(p);
                } else {
                    side1.pb(p);
                }
            }
            auto hull0 = convex_hull(side0), hull1 = convex_hull(side1);
            if (sz(side0) == sz(side1)) {
                rv = min(rv, n - sz(hull0) - sz(hull1));
            }
            side0.clear(), side1.clear();
            FORE (p, pts) {
                if (p == pi) {
                    side1.pb(pi);
                    continue;
                } elif (p == pj) {
                    side0.pb(pj);
                    continue;
                }
                ld val = (pj.first - pi.first) * (p.second - pi.second) -
                    (pj.second - pi.second) * (p.first - pi.first);
                if (val > 0) {
                    side0.pb(p);
                } else {
                    side1.pb(p);
                }
            }
            hull0 = convex_hull(side0), hull1 = convex_hull(side1);
            if (sz(side0) == sz(side1)) {
                rv = min(rv, n - sz(hull0) - sz(hull1));
            }
        }
    }
    assert(rv != 1e18);
    cout << rv << '\n';

    return 0;
}