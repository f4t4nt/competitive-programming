#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

ll tri_area(vector<ll> x, vector<ll> y) {
    return (x[0] * (y[1] - y[2]) -
            x[1] * (y[0] - y[2]) +
            x[2] * (y[0] - y[1]));
}

// angle from axis (1-2) to vec (1-0)
ld get_ang(vector<ll> x, vector<ll> y) {
    vector<ll> w = {x[0] - x[1], y[0] - y[1]},
            v = {x[2] - x[1], y[2] - y[1]};
// angle from v to w
    return atan2(w[1] * v[0] - w[0] * v[1],
        w[0] * v[0] + w[1] * v[1]);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n; cin >> n;
    vector<ll> x(n), y(n);
    FOR (i, n) cin >> x[i] >> y[i];
    ll x0, y0, x1, y1, area = 0;
    cin >> x0 >> y0 >> x1 >> y1;
    FOR (i, n) {
        ll j = (i + 1) % n;
        area += tri_area(
            {0, x[i], x[j]},
            {0, y[i], y[j]}
        );
    }
    if (area < 0) {
        // cout << "flipped\n";
        flip(x), flip(y);
    }
    vector<pair<ll, ll>> pts;
    FOR (i, n) {
        ll j = (i + 1) % n;
        ll mnx = min(x[i], x[j]),
            mxx = max(x[i], x[j]),
            mny = min(y[i], y[j]),
            mxy = max(y[i], y[j]);
        if (mnx <= x0 && x0 <= mxx &&
            mny <= y0 && y0 <= mxy &&
            tri_area(
                {x[i], x0, x[j]},
                {y[i], y0, y[j]}
            ) == 0)
        {
            // cout << x[i] << ',' << y[i] << ' '
            //     << x[j] << ',' << y[j] << '\n';
            pts.pb({x[j] * 2 - x[i], y[j] * 2 - y[i]});
        }
    }
    set<ll> rv;
    for (auto [px, py] : pts) {
        // ll cur = tri_area(
        //     {px, x0, x1},
        //     {py, y0, y1}
        // );
        ld cur = get_ang(
            {px, x0, x1},
            {py, y0, y1}
        ) * 180 / M_PI;
        if (cur == 0 || cur == 180 || cur == -180) rv.insert(0);
        elif (cur > 0) rv.insert(1);
        else rv.insert(-1);
    }
    if (sz(rv) != 1) {
        cout << "?\n";
    } else {
        ll tmp = *rv.begin();
        if (tmp == 0) cout << "?\n";
        elif (tmp == 1) cout << "outside\n";
        else cout << "inside\n";
    }

    return 0;
}