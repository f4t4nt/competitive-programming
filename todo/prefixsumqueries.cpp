#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
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
#define FOB(x, b, e) for(auto x = b; x < e; x++)
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

// https://cses.fi/problemset/task/2166/

struct SumSegTree { // returns sum of range
    ll n;
    vector<ll> data, lazy;
    SumSegTree (ll n) : n(n), data(4 * n, 0), lazy(4 * n, 0) {}
    void update(ll lo, ll hi, ll val, ll i = 1, ll l = 0, ll r = -1) { // [lo, hi)
        if (r == -1) r = n;
        if (lazy[i] != 0) {
            data[i] += (r - l) * lazy[i];
            if (r - l > 1) {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
        if (lo <= l && r <= hi) {
            data[i] += (r - l) * val;
            if (r - l > 1) {
                lazy[2 * i] += val;
                lazy[2 * i + 1] += val;
            }
            return;
        }
        if (r <= lo || hi <= l) return;
        ll m = (l + r) / 2;
        update(lo, hi, val, 2 * i, l, m);
        update(lo, hi, val, 2 * i + 1, m, r);
        data[i] = data[2 * i] + data[2 * i + 1];
    }
    ll query(ll lo, ll hi, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (lazy[i] != 0) {
            data[i] += (r - l) * lazy[i];
            if (r - l > 1) {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
        if (lo <= l && r <= hi) return data[i];
        if (r <= lo || hi <= l) return 0;
        ll m = (l + r) / 2;
        return query(lo, hi, 2 * i, l, m) + query(lo, hi, 2 * i + 1, m, r);
    }
};

struct PreSegTree { // returns max prefix sum in range
    ll n;
    vector<ll> data, lazy;
    PreSegTree (ll n) : n(n), data(4 * n, 0), lazy(4 * n, 0) {}
    void update(ll lo, ll hi, ll val, ll i = 1, ll l = 0, ll r = -1) { // [lo, hi)
        if (r == -1) r = n;
        if (lazy[i] != 0) {
            data[i] += lazy[i];
            if (r - l > 1) {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
        if (lo <= l && r <= hi) {
            data[i] += val;
            if (r - l > 1) {
                lazy[2 * i] += val;
                lazy[2 * i + 1] += val;
            }
            return;
        }
        if (hi <= l) lazy[i] += val;
        if (r <= lo || hi <= l) return;
        ll m = (l + r) / 2;
        update(lo, hi, val, 2 * i, l, m);
        update(lo, hi, val, 2 * i + 1, m, r);
        data[i] = max(data[2 * i], data[2 * i + 1]);
    }
    ll query(ll lo, ll hi, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (lazy[i] != 0) {
            data[i] += lazy[i];
            if (r - l > 1) {
                lazy[2 * i] += lazy[i];
                lazy[2 * i + 1] += lazy[i];
            }
            lazy[i] = 0;
        }
        if (lo <= l && r <= hi) return data[i];
        if (r <= lo || hi <= l) return 0;
        ll m = (l + r) / 2;
        return max(query(lo, hi, 2 * i, l, m), query(lo, hi, 2 * i + 1, m, r));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, q;
    cin >> n >> q;
    SumSegTree st_sum(n);
    PreSegTree st_pre(n);
    vector<ll> x(n);
    FOR (i, n) {
        cin >> x[i];
        st_sum.update(i, i + 1, x[i]);
        st_pre.update(i, i + 1, x[i]);
    }
    while (q--) {
        ll t, a, b;
        cin >> t >> a >> b;
        if (t == 1) {
            a--;
            st_sum.update(a, a + 1, b - x[a]);
            st_pre.update(a, a + 1, b - x[a]);
            x[a] = b;
        } else {
            a--;
            ll sum = st_sum.query(0, a),
                pre = st_pre.query(a, b),
                rv = max(0LL, pre - sum);
            cout << rv << '\n';
        }
    }

    return 0;
}