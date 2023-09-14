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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    // {x, {y1, y2, i}}
    // [x, y1] [x, y2]
    map<ll, vector<tuple<ll, ll, ll>>> vert;
    // {x1, y, 2 * i}
    // {x2, y, 2 * i + 1}
    // [x1, y] [x2, y]
    // OR
    // {x, 0, -1} MEANS VERT PRESENT
    set<tuple<ll, ll, ll>> hori;
    FOR (i, n) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) {
            if (y1 > y2) {
                swap(y1, y2);
            }
            vert[x1].pb({y1, y2, i});
            hori.insert({x1, 0, -1});
        } else {
            if (x1 > x2) {
                swap(x1, x2);
            }
            hori.insert({x1, y1, 2 * i});
            hori.insert({x2, y2, 2 * i + 1});
        }
    }
    ll rv = 0;
    indexed_set active;
    FORE (e, hori) {
        auto [x, y, i] = e;
        if (i == -1) { // check vert
            FORE (seg, vert[x]) {
                auto [y1, y2, i] = seg;
                rv += active.order_of_key({y2 + 1, -1}) - active.order_of_key({y1, -1});
            }
        } elif (i & 1) { // remove
            active.erase({y, i / 2});
        } else { // add
            active.insert({y, i / 2});
        }
    }
    cout << rv << '\n';

    return 0;
}