#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
 
#pragma GCC target("popcnt,lzcnt")
 
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

// imma show YOU how great i am.

vector<pair<ll, ll>> convex_hull(vector<pair<ll, ll>> pts) {
    if (sz(pts) <= 1) return pts;
    sort(all(pts));
    vector<pair<ll, ll>> h(sz(pts) + 1);
    int s = 0, t = 0;
    FOR (it, 2) {
        FOR (i, sz(pts)) {
            auto p = pts[i];
            while (t >= s + 2 && (h[t - 2].first - h[t - 1].first) * (p.second - h[t - 1].second) - (h[t - 2].second - h[t - 1].second) * (p.first - h[t - 1].first) <= 0) t--;
            h[t++] = p;
        }
        s = t--;
        reverse(all(pts));
    }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, k;
    cin >> n;
    vector<pair<ll, ll>> pts(n), seats;
    FOR(i, n) {
        cin >> pts[i].first >> pts[i].second;
    }
    cin >> k;
    seats.resize(k);
    FOR(i, k) {
        cin >> seats[i].first >> seats[i].second;
    }
    auto hull = convex_hull(pts);
    pair<ll, pair<ll, ll>> rv = {LLONG_MAX, {0, 0}};
    FOR (i, k) {
        ll x = seats[i].first, y = seats[i].second, maxd = 0;
        FORE (p, hull) {
            maxd = max(maxd, (x - p.first) * (x - p.first) + (y - p.second) * (y - p.second));
        }
        rv = min(rv, {maxd, {x, y}});
    }
    cout << rv.second.first << ' ' << rv.second.second << '\n';

    return 0;
}