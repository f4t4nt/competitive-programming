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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ll n, rv = 0;
        cin >> n;
        if (n == 0) {
            break;
        }
        vector<pair<ll, ll>> v(n);
        FOR (i, n) {
            cin >> v[i].first >> v[i].second;
        }
        FOR (i, n) {
            FOB (j, i + 1, n) {
                FOB (k, j + 1, n) {
                    FOB (l, k + 1, n) {
                        vector<pair<ld, ld>> points = {v[i], v[j], v[k], v[l]};
                        auto hull = convex_hull(points);
                        if (sz(hull) == 4) {
                            rv++;
                        }
                    }
                }
            }
        }
        cout << rv << '\n';
    }

    return 0;
}