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
    ll,
    null_type,
    less<ll>,
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

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

struct SegTree {
    ll n;
    SegTree (ll n) : n(n) {}
    void qry(ll ql, ll qr, vector<pll> &ref, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            ref.pb({l, r});
            return;
        }
        ll m = (l + r) / 2;
        qry(ql, qr, ref, 2 * i, l, m);
        qry(ql, qr, ref, 2 * i + 1, m, r);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    SegTree st(1 << 20);

    ll t; cin >> t;
    while (t--) {
        ll l1, l2, r1, r2; cin >> l1 >> r1 >> l2 >> r2;
        vector<pll> ref1, ref2;
        st.qry(l1, r1, ref1);
        st.qry(l2, r2, ref2);
        ll ans = 0;
        for (auto [f1, s1] : ref1) {
            ll rng1 = s1 - f1;
            for (auto [f2, s2] : ref2) {
                ll rng2 = s2 - f2;
                ans += max(rng1, rng2) / min(rng1, rng2);
            }
        }
        cout << ans << '\n';
    }

    return 0;
}