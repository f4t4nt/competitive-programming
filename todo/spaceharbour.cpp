#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
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

// https://codeforces.com/contest/1924/problem/B

struct SegTree {
    ll n;
    vector<ll> data, lazy;
    SegTree (ll n) : n(n), data(4 * n), lazy(4 * n) {}
    void push(ll i, ll l, ll r) {
        if (lazy[i] == -1) return;
        data[i] = (r - l) * lazy[i];
        if (r - l > 1) {
            lazy[2 * i] = lazy[i];
            lazy[2 * i + 1] = lazy[i];
        }
        lazy[i] = -1;
    }
    void update(ll ul, ll ur, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n;
        push(i, l, r);
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            lazy[i] = val;
            push(i, l, r);
            return;
        }
        ll m = (l + r) / 2;
        update(ul, ur, val, 2 * i, l, m);
        update(ul, ur, val, 2 * i + 1, m, r);
        data[i] = data[2 * i] + data[2 * i + 1];
    }
    ll query(ll ql, ll qr, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        push(i, l, r);
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return data[i];
        ll m = (l + r) / 2;
        return query(ql, qr, 2 * i, l, m) + query(ql, qr, 2 * i + 1, m, r);
    }
    void print(ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        cout << "[" << l << ", " << r << "): " << data[i] << " " << lazy[i] << '\n';
        if (r - l > 1) {
            ll m = (l + r) / 2;
            print(2 * i, l, m);
            print(2 * i + 1, m, r);
        }
    }
};

// cost of moving ships at [l, r]
// v_l * (sum_{i = l}^{r} nxt[i] - (r - l + 1) * (l + r) / 2)
ll get_cost(ll l, ll r, SegTree &nxt, map<ll, ll> &vals) {
    assert(vals.lower_bound(l) == vals.lower_bound(r - 1));
    ll v_l, nxt_sum = nxt.query(l, r + 1),
        i_sum = (r - l + 1) * (l + r) / 2;
    auto it = vals.lower_bound(l);
    if (it != vals.begin()) {
        it--;
        v_l = it->second;
    } else v_l = 0;
    return v_l * (nxt_sum - i_sum);
}

struct BIT {
    vector<ll> tree; ll n;
    BIT(ll n) : n(n) { tree.resize(n + 1); }
    void update(ll idx, ll val) {
        idx++;
        while (idx <= n)
        { tree[idx] = val; idx += idx & (-idx); }
    }
    ll query(ll idx) {
        idx++; ll sum = 0;
        while (idx > 0)
        { sum += tree[idx]; idx -= idx & (-idx); }
        return sum;
    }
    ll query(ll l, ll r) { return query(r) - query(l - 1); }
    void print() {
        FOR (i, n) cout << i << ": " << query(i, i) << '\n';
    }
};

ll brute(ll l, ll r, map<ll, ll> &vals) {
    ll rv = 0;
    FOB (i, l, r + 1) {
        auto it = vals.lower_bound(i);
        ll prv_val = 0;
        if (it != vals.begin()) {
            it--;
            prv_val = it->second;
        }
        it = vals.lower_bound(i);
        ll dst = it->first;
        rv += prv_val * (dst - i);
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, q; cin >> n >> m >> q;
    vector<ll> x0(m), v0(m);
    SegTree nxt(n + 1);
    FOR (i, m) cin >> x0[i];
    FOR (i, m) cin >> v0[i];
    map<ll, ll> vals;
    FOR (i, m) vals[x0[i]] = v0[i];
    ll prv_k = 0;
    BIT costs(n + 1);
    for (auto [k, v] : vals) {
        nxt.update(prv_k, k + 1, k);
        costs.update(prv_k, get_cost(prv_k, k, nxt, vals));
        prv_k = k + 1;
    }
    while (q--) {
        ll t; cin >> t;
        if (t == 1) {
            ll k, v; cin >> k >> v;
            vals[k] = v;
            // find prv_k
            auto it = vals.lower_bound(k);
            ll prv_k = 0;
            if (it != vals.begin()) {
                it--;
                prv_k = it->first + 1;
            }
            return 0;
        } else {
            ll l, r, lo, hi; cin >> l >> r;
            // cout << brute(l, r, vals) << '\n';
            ll tv = brute(l, r, vals);
            auto it = vals.upper_bound(r);
            it--;
            hi = it->first;
            it = vals.lower_bound(l);
            lo = it->first;
            ll rv = 0;
            if (l <= lo && lo <= hi && hi <= r) {
                rv = costs.query(lo, hi);
                assert(rv <= tv);
                rv += get_cost(l, lo, nxt, vals);
                rv += get_cost(hi, r, nxt, vals);
            } else rv = get_cost(l, r, nxt, vals);
            assert(rv <= tv);
            cout << rv << '\n';
        }
    }

    return 0;
}