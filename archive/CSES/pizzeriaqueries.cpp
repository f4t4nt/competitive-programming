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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

struct SegTree {
    ll n;
    // min(p + a) - b : a >= b, b is on the left of a
    // min(p - a) + b : a <= b, b is on the right of a
    vector<ll> left, right;
    SegTree (ll n) : n(n), left(4 * n, 1e18), right(4 * n, 1e18) {}
    void update(ll ui, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ui, ui + 1)
        if (r == -1) r = n;
        if (ui < l || r <= ui) return;
        if (ui == l && r - l == 1) {
            left[i] = val + ui;
            right[i] = val - ui;
            return;
        }
        ll m = (l + r) / 2;
        update(ui, val, 2 * i, l, m);
        update(ui, val, 2 * i + 1, m, r);
        left[i] = min(left[2 * i], left[2 * i + 1]);
        right[i] = min(right[2 * i], right[2 * i + 1]);
    }
    // return left[i] - qi if qi <= l
    // return right[i] + qi if qi >= r
    // return min(left[i] - qi, right[i] + qi) if l < qi < r
    ll query(ll ql, ll qr, ll qi, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (qi <= l) return left[i] - qi;
        if (qi >= r) return right[i] + qi;
        ll m = (l + r) / 2;
        return min(query(ql, qr, qi, 2 * i, l, m), query(ql, qr, qi, 2 * i + 1, m, r));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, q;
    cin >> n >> q;
    SegTree st(n);
    FOR (i, n) {
        ll a;
        cin >> a;
        st.update(i, a);
    }
    while (q--) {
        ll t, k;
        cin >> t >> k;
        k--;
        if (t == 1) {
            ll u;
            cin >> u;
            st.update(k, u);
        } else {
            cout << st.query(0, n, k) << '\n';
        }
    }

    return 0;
}