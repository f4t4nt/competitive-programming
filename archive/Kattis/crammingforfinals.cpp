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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll r, c, d, n; cin >> r >> c >> d >> n;
    r--, c--;
    ll area = 0;
    FOB (i, 1, d + 1) area += (ll) sqrt(d * d - i * i) + 1;
    area = 4 * area + 1;
    // ll tmp = 0;
    // FOB (i, -d, d + 1) FOB (j, -d, d + 1) tmp += (i * i + j * j <= d * d);
    if (area * n < r * c) {
        cout << 0 << '\n';
        return 0;
    }
    vector<pll> centers(n);
    map<ll, vector<ll>> events;
    events[0] = {};
    events[r] = {};
    set<ll> active;
    set<pll> ref;
    FOR (i, n) {
        pll &pt = centers[i];
        cin >> pt.f >> pt.s;
        pt.f--, pt.s--;
        ref.insert(pt);
        if (pt.f > d) events[pt.f - d].pb(2 * i);
        else active.insert(i);
        if (pt.f + d + 1 <= r) events[pt.f + d + 1].pb(2 * i + 1);
    }
    ll ans = n;
    auto cur = events.begin();
    auto nxt = next(cur);
    while (cur != events.end()) {
        FORE (x, cur->s) {
            if (x % 2) active.erase(x / 2);
            else active.insert(x / 2);
        }
        if (!sz(active)) ans = 0;
        ll x = cur->f;
        while (x <= r && x != nxt->f) {
            if (!ans) break;
            ll tmp = 0;
            map<ll, ll> cur_events;
            cur_events[0] = 0;
            cur_events[c] = 0;
            FORE (idx, active) {
                ll del = sqrt(d * d - (x - centers[idx].f) * (x - centers[idx].f));
                ll lo = max(0ll, centers[idx].s - del);
                ll hi = min(c, centers[idx].s + del);
                cur_events[lo]++;
                cur_events[hi + 1]--;
            }
            FORE (y, cur_events) {
                if (y.f > c) break;
                tmp += y.s;
                if (!ref.count({x, y.f})) ans = min(ans, tmp);
            }
            x++;
        }
        if (!ans) break;
        cur++, nxt++;
    }
    cout << ans << '\n';

    return 0;
}