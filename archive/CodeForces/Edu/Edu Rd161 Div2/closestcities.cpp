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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t; cin >> t;
    while (t--) {
        ll n, q; cin >> n;
        vector<ll> a(n + 1, -1e18), l2r(n + 2), r2l(n + 2);
        FOR (i, n) cin >> a[i + 1];
        a.pb(1e18);
        FOB (i, 1, n + 1) {
            ll prv = abs(a[i] - a[i - 1]), nxt = abs(a[i + 1] - a[i]);
            if (prv > nxt) l2r[i + 1] = l2r[i] + 1;
            else l2r[i + 1] = l2r[i] + nxt;
        }
        for (ll i = n; i >= 1; i--) {
            ll prv = abs(a[i] - a[i - 1]), nxt = abs(a[i + 1] - a[i]);
            if (nxt > prv) r2l[i - 1] = r2l[i] + 1;
            else r2l[i - 1] = r2l[i] + prv;
        }
        cin >> q;
        while (q--) {
            ll x, y; cin >> x >> y;
            if (y > x) cout << l2r[y] - l2r[x] << '\n';
            else cout << r2l[y] - r2l[x] << '\n';
        }
    }

    return 0;
}