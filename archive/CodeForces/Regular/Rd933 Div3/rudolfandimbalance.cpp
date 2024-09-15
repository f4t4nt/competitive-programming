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

ll eval(ll x, set<ll> &func, ll lo, ll hi) {
    ll mid = (lo + hi) / 2;
    auto it = func.lower_bound(mid - x);
    ll y = *it;
    if (it != func.begin()) {
        it--;
        if (abs(mid - x - *it) < abs(mid - x - y)) y = *it;
    }
    return x + y;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m, k; cin >> n >> m >> k;
        vector<ll> a(n);
        FOR (i, n) cin >> a[i];
        set<ll> model, func;
        FOR (i, m) {
            ll x; cin >> x;
            model.insert(x);
        }
        FOR (i, k) {
            ll x; cin >> x;
            func.insert(x);
        }
        ll mx_d = 0, lo, hi;
        map<ll, ll> cnt;
        FOR (i, n - 1) {
            ll d = a[i + 1] - a[i];
            cnt[d]++;
            if (d > mx_d) {
                mx_d = d;
                lo = a[i];
                hi = a[i + 1];
            }
        }
        if (cnt[mx_d] > 1) {
            cout << mx_d << '\n';
            continue;
        }
        ll ans = mx_d;
        FORE (x, model) {
            ll val = eval(x, func, lo, hi);
            if (val >= lo && val <= hi)
                ans = min(ans, max(val - lo, hi - val));
            val = eval(x, func, lo, hi + 1);
            if (val >= lo && val <= hi)
                ans = min(ans, max(val - lo, hi - val));
        }
        if (sz(cnt) == 1) cout << ans << '\n';
        else {
            auto it = cnt.rbegin(); it++;
            cout << max(ans, it->f) << '\n';
        }
    }

    return 0;
}