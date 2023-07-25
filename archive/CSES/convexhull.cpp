#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

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
            if ((p2.second - p1.second) * (p.first - p2.first) > (p.second - p2.second) * (p2.first - p1.first)) {
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
            if ((p2.second - p1.second) * (p.first - p2.first) > (p.second - p2.second) * (p2.first - p1.first)) {
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<pair<ll, ll>> pts(n);
    FOR (i, n) {
        cin >> pts[i].first >> pts[i].second;
    }
    auto hull = convex_hull(pts);
    cout << sz(hull) << '\n';
    FORE (p, hull) {
        cout << p.first << ' ' << p.second << '\n';
    }

    return 0;
}