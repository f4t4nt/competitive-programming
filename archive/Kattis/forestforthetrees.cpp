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
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
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

#define x first
#define y second

pll rotate90(pll p) {
    return {p.y, -p.x};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m, d; cin >> n >> m >> d;
    vector<pll> trees(n);
    set<pll> sensed;
    FOR(i, n) cin >> trees[i].x >> trees[i].y;
    FOR(i, m) {
        ll x, y; cin >> x >> y;
        sensed.insert({x, y});
    }
    sensed.erase({0, 0});
    vector<pll> ans;
    FOR (_, 4) {
        ll x0 = sensed.begin()->x, y0 = sensed.begin()->y;
        FORE (p, trees) {
            bool ok = true;
            ll rx = p.x - x0, ry = p.y - y0, cnt = 0;
            FORE (q, trees) {
                ll dx = q.x - rx, dy = q.y - ry;
                if (abs(dx) + abs(dy) <= d) {
                    if (sensed.count({dx, dy})) cnt++;
                    else {
                        ok = false;
                        break;
                    }
                }
            }
            ok &= cnt == m;
            if (ok) ans.pb({rx, ry});
            if (sz(ans) > 1) break;
        }
        if (sz(ans) > 1) break;
        set<pll> sensed90;
        FORE (p, sensed) sensed90.insert(rotate90(p));
        sensed = sensed90;
    }
    if (sz(ans) == 0) cout << "Impossible\n";
    elif (sz(ans) == 1) cout << ans[0].x << ' ' << ans[0].y << '\n';
    else cout << "Ambiguous\n";

    return 0;
}