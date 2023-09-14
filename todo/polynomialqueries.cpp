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

// https://cses.fi/problemset/task/1736/

struct SegTree {
    ll n;
    vector<ll> data, lazy, lazy2;
    SegTree (ll n) : n(n), data(4 * n, 0), lazy(4 * n, 0), lazy2(4 * n, 0) {}
    void push(ll i, ll l, ll r) {
        if (lazy[i] == 0) return;
        // assert(((lazy[i] + lazy2[i]) * (r - l)) % 2 == 0);
        data[i] += (lazy[i] + lazy2[i]) * (r - l);
        if (r - l > 1) {
            ll del = (l + r) / 2 - l;
            lazy[2 * i] += lazy[i];
            lazy2[2 * i] += lazy[i] + del - 1;
            lazy[2 * i + 1] += lazy[i] + del;
            lazy2[2 * i + 1] += lazy2[i];
        }
        lazy[i] = 0;
        lazy2[i] = 0;
    }
    void push_rec(ll i, ll l, ll r) {
        if (r - l == 1) return;
        push(i, l, r);
        ll m = (l + r) / 2;
        push_rec(2 * i, l, m);
        push_rec(2 * i + 1, m, r);
    }
    void push_all() {
        push_rec(1, 0, n);
    }
    vector<ll> unwrap() {
        push_all();
        vector<ll> rv(n);
        FOR (i, n) {
            rv[i] = query(i, i + 1);
        }
        return rv;
    }
    void init(ll ui, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n;
        if (ui < l || r <= ui) return;
        if (ui == l && r - l == 1) {
            data[i] = val;
            return;
        }
        ll m = (l + r) / 2;
        init(ui, val, 2 * i, l, m);
        init(ui, val, 2 * i + 1, m, r);
        data[i] = data[2 * i] + data[2 * i + 1];
    }
    void update(ll ul, ll ur, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n;
        push(i, l, r);
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            lazy[i] += l - ul + 1;
            lazy2[i] += r - ul;
            push(i, l, r);
            return;
        }
        ll m = (l + r) / 2, del = m - l;
        update(ul, ur, 2 * i, l, m);
        update(ul, ur, 2 * i + 1, m, r);
        data[i] = data[2 * i] + data[2 * i + 1];
    }
    ll query(ll ql, ll hr, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        push(i, l, r);
        if (hr <= l || r <= ql) return 0;
        if (ql <= l && r <= hr) return data[i];
        ll m = (l + r) / 2;
        return query(ql, hr, 2 * i, l, m) + query(ql, hr, 2 * i + 1, m, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, q;
    cin >> n >> q;
    // vector<ll> bash(n);
    SegTree st(n);
    FOR (i, n) {
        ll x;
        cin >> x;
        // bash[i] = x;
        st.init(i, 2 * x);
    }
    while (q--) {
        ll t, a, b;
        cin >> t >> a >> b;
        if (t == 1) {
            st.update(a - 1, b);
            // FOB (i, a - 1, b) {
            //     bash[i] += i - a + 2;
            // }
        } else {
            ll rv = st.query(a - 1, b);
            rv /= 2;
            // ll rv2 = 0;
            // FOB (i, a - 1, b) {
            //     rv2 += bash[i];
            // }
            // assert(rv == rv2);
            cout << rv << '\n';
        }
        // st.push_all();
        // auto ref = st.unwrap();
        // assert(ref == bash);
    }

    return 0;
}