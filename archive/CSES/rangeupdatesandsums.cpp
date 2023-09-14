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
    vector<ll> data, lazy;
    vector<bool> lazy2;
    SegTree (ll n) : n(n), data(4 * n, 0), lazy(4 * n, 0), lazy2(4 * n, false) {}
    void push(ll i, ll l, ll r) {
        if (lazy[i] == 0) return;
        if (lazy2[i]) { // set
            data[i] = (r - l) * lazy[i];
            if (r - l > 1) {
                lazy[2 * i] = lazy[i];
                lazy[2 * i + 1] = lazy[i];
                lazy2[2 * i] = true;
                lazy2[2 * i + 1] = true;
            }
        } else {
            data[i] += (r - l) * lazy[i];
            if (r - l > 1) {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
        }
        lazy[i] = 0;
        lazy2[i] = false;
    }
    void update(ll ul, ll ur, bool type2, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n;
        push(i, l, r);
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            if (type2) {
                lazy[i] = val;
                lazy2[i] = true;
            } else {
                lazy[i] += val;
            }
            push(i, l, r);
            return;
        }
        ll m = (l + r) / 2;
        update(ul, ur, type2, val, 2 * i, l, m);
        update(ul, ur, type2, val, 2 * i + 1, m, r);
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
    SegTree st(n);
    FOR (i, n) {
        ll x;
        cin >> x;
        st.update(i, i + 1, false, x);
    }
    while (q--) {
        ll t;
        cin >> t;
        if (t == 1) {
            ll l, r, x;
            cin >> l >> r >> x;
            st.update(l - 1, r, false, x);            
        } elif (t == 2) {
            ll l, r, x;
            cin >> l >> r >> x;
            st.update(l - 1, r, true, x);
        } else {
            ll l, r;
            cin >> l >> r;
            cout << st.query(l - 1, r) << '\n';
        }
    }

    return 0;
}