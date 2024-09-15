#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

void tmp() {
    ll n; cin >> n;
    vector<pll> pts(n);
    FOR (i, n) cin >> pts[i].f >> pts[i].s;
    set<ll> dists;
    FOR (i, n) FOB (j, i, n)
        dists.insert(abs(pts[i].f - pts[j].f) +
            abs(pts[i].s - pts[j].s));
    cout << sz(dists) << endl;
}

ll tmp(vector<pll> pts) {
    ll n = sz(pts);
    set<ll> dists;
    FOR (i, n) FOB (j, i, n)
        dists.insert(abs(pts[i].f - pts[j].f) +
            abs(pts[i].s - pts[j].s));
    return sz(dists);
}

ll tmp(set<pll> pts) {
    ll n = sz(pts);
    set<ll> dists;
    FORE (p0, pts) FORE (p1, pts)
        dists.insert(abs(p0.f - p1.f) + abs(p0.s - p1.s));
    return sz(dists);
}

bool insert_pt(set<pll> &pts, ll x, ll y, ll cnt) {
    if (pts.find({x, y}) != pts.end()) return false;
    pts.insert({x, y});
    if (tmp(pts) >= cnt) return true;
    pts.erase({x, y});
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    // while (true) tmp();
    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<pll> ans = {{1,1}};
        if (n == 2) ans.pb({1,2});
        elif (n == 3) {
            ans.pb({2, 1});
            ans.pb({2, 3});
        } else {
            ans.pb({n, n});
            ll dx = 1;
            while (sz(ans) < n) {
                if (dx % 4 == 0) ans.pb({1 + dx, 1});
                elif (dx % 4 == 1) ans.pb({1, 1 + dx});
                elif (dx % 4 == 2) ans.pb({n - dx, n});
                else ans.pb({n, n - dx});
                dx++;
            }
        }
        // assert(tmp(ans) == min(n * (n - 1) / 2 + 1, 2 * n - 1));
        FORE (p, ans) cout << p.f << ' ' << p.s << '\n';
    }

    return 0;
}