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

vector<pair<ll, ll>> convex_hull(vector<pair<ll, ll>> pts) {
    ssort(pts); // sort points by x-coordinate
    vector<pair<ll, ll>> lo; // lower hull
    for (auto &p : pts) {
        while (sz(lo) >= 2) {
            auto &p1 = lo[sz(lo) - 2];
            auto &p2 = lo[sz(lo) - 1];
            if ((p2.second - p1.second) * (p.first - p2.first) >= (p.second - p2.second) * (p2.first - p1.first)) {
                lo.pop_back();
            } else {
                break;
            }
        }
        lo.pb(p);
    }
    vector<pair<ll, ll>> hi; // upper hull
    for (auto it = pts.rbegin(); it != pts.rend(); it++) {
        auto &p = *it;
        while (sz(hi) >= 2) {
            auto &p1 = hi[sz(hi) - 2];
            auto &p2 = hi[sz(hi) - 1];
            if ((p2.second - p1.second) * (p.first - p2.first) >= (p.second - p2.second) * (p2.first - p1.first)) {
                hi.pop_back();
            } else {
                break;
            }
        }
        hi.pb(p);
    }
    lo.pop_back(); // remove duplicates
    hi.pop_back();
    lo.insert(lo.end(), hi.begin(), hi.end()); // merge lower and upper hulls
    return lo;
}

ld perimeter(vector<pair<ll, ll>> pts) {
    ld p = 0;
    FOR (i, sz(pts)) {
        auto &p1 = pts[i];
        auto &p2 = pts[(i + 1) % sz(pts)];
        p += sqrt((p1.first - p2.first) * (p1.first - p2.first)
            + (p1.second - p2.second) * (p1.second - p2.second));
    }
    return p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (true) {
        ll n;
        cin >> n;
        if (n == 0) {
            break;
        }
        vector<pair<ll, ll>> pts(n);
        map<pair<ll, ll>, pair<ll, ll>> ref;
        FOR (i, n) {
            ll x, y, v, l;
            cin >> x >> y >> v >> l;
            pts[i] = {x, y};
            ref[{x, y}] = {v, l};
        }
        ll rv = 1e18;
        FOB (i, 1, 1 << n) {
            ll tmp = 0;
            ld len = 0;
            vector<pair<ll, ll>> npts;
            FOR (j, n) {
                if (i & (1 << j)) {
                    npts.pb(pts[j]);
                } else {
                    tmp += ref[pts[j]].first;
                    len += ref[pts[j]].second;
                }
            }
            auto ch = convex_hull(npts);
            ld p = perimeter(ch);
            if (p > len) {
                continue;
            }
            rv = min(rv, tmp);
        }
        cout << "The lost value is " << rv << ".\n";
    }

    return 0;
}