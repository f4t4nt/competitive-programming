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
    vector<ll> data_sum, data_pre;
    SegTree (ll n) : n(n), data_sum(4 * n, 0), data_pre(4 * n, 0) {}
    void update(ll ui, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ui, ui + 1)
        if (r == -1) r = n;
        if (ui < l || r <= ui) return;
        if (ui == l && r - l == 1) {
            data_sum[i] = val;
            data_pre[i] = max(0LL, val);
            return;
        }
        ll m = (l + r) / 2;
        update(ui, val, 2 * i, l, m);
        update(ui, val, 2 * i + 1, m, r);
        data_sum[i] = data_sum[2 * i] + data_sum[2 * i + 1];
        data_pre[i] = max(data_pre[2 * i], data_sum[2 * i] + data_pre[2 * i + 1]);
    }
    pair<ll, ll> query(ll ql, ll qr, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (qr <= l || r <= ql) return {0, 0};
        if (ql <= l && r <= qr) return {data_sum[i], data_pre[i]};
        ll m = (l + r) / 2;
        auto left = query(ql, qr, 2 * i, l, m),
             right = query(ql, qr, 2 * i + 1, m, r);
        return {left.first + right.first, max(left.second, left.first + right.second)};
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
        ll t, a, b;
        cin >> t >> a >> b;
        a--;
        if (t == 1) {
            st.update(a, b);
        } else {
            cout << st.query(a, b).second << '\n';
        }
    }

    return 0;
}