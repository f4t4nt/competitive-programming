#include <bits/stdc++.h>

using namespace std;

using ll = long long;
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
#define FOB(x, b, e) for(ll x = b; x < (ll) e; x++)
#define FORE(x, C) for (auto &x : C)

vector<pair<ll, ll>> convex_hull(vector<pair<ll, ll>> points) {
    ssort(points);
    vector<pair<ll, ll>> lower, upper;
    FORE (p, points) {
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
    FORR (i, sz(points)) {
        auto &p = points[i];
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
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), all(upper));
    return lower;
}

ll dist2(pair<ll, ll> a, pair<ll, ll> b) {
    return (a.first - b.first) * (a.first - b.first) +
        (a.second - b.second) * (a.second - b.second);
}

int main() {
    ll n;
    cin >> n;
    vector<pair<ll, ll>> pts(n);
    FOR (i, n) {
        cin >> pts[i].first >> pts[i].second;
    }
    auto hull = convex_hull(pts);
    ll rv = 0;
    ll i = 0;
    while (i < sz(hull)) {
        ll j = 0;
        while (j < sz(hull)) {
            ll cur_d = dist2(hull[i], hull[j]);
            rv = max(cur_d, rv);
            j++;
        }
        i++;
    }
    ld tmp = sqrt(rv);
    cout << fixed << setprecision(10) << tmp << '\n';

    return 0;
}