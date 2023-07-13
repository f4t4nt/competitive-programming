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
    // sort points by x-coordinate
    ssort(pts);

    // lower hull
    vector<pair<ll, ll>> lo;
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

    // upper hull
    vector<pair<ll, ll>> hi;
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

    // remove duplicates
    lo.pop_back();
    hi.pop_back();

    // merge lower and upper hulls
    lo.insert(lo.end(), hi.begin(), hi.end());
    return lo;
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
        set<pair<ll, ll>> s;
        FOR (i, n) {
            ll x, y;
            cin >> x >> y;
            s.insert({x, y});
        }
        if (sz(s) == 1) {
            cout << 1 << '\n';
            cout << s.begin()->first << ' ' << s.begin()->second << '\n';
            continue;
        } else if (sz(s) == 2) {
            cout << 2 << '\n';
            FORE (p, s) {
                cout << p.first << ' ' << p.second << '\n';
            }
            continue;
        }
        vector<pair<ll, ll>> pts(all(s));
        auto hull = convex_hull(pts);
        cout << sz(hull) << '\n';
        FORE (p, hull) {
            cout << p.first << ' ' << p.second << '\n';
        }
    }

    return 0;
}