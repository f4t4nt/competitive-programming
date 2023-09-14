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

bool solve(vector<pair<ll, ll>> pts, ll cnt = 3) {
    if (cnt == 0) {
        return sz(pts) == 0;
    }
    if (sz(pts) <= cnt * 2) {
        return true;
    }
    ll i = rand() % sz(pts), j = rand() % sz(pts);
    while (i == j) {
        j = rand() % sz(pts);
    }
    vector<pair<ll, ll>> pts_new;
    FORE (pt, pts) {
        if ((pt.first - pts[i].first) * (pts[j].second - pts[i].second) !=
            (pt.second - pts[i].second) * (pts[j].first - pts[i].first)) {
            pts_new.pb(pt);
        }
    }
    return solve(pts_new, cnt - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<pair<ll, ll>> pts(n);
    FORE (pt, pts) {
        cin >> pt.first >> pt.second;
    }
    bool ok = false;
    FOR (i, 1000) {
        if (solve(pts)) {
            ok = true;
            break;
        }
    }
    cout << (ok ? "possible" : "impossible") << '\n';

    return 0;
}