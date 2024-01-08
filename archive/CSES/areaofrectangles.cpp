#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
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

struct SegTree {
    ll n;
    vector<ll> mn, cnt, lazy;
    SegTree (ll n) : n(n), mn(4 * n), cnt(4 * n), lazy(4 * n) {
        init();
    }
    void init(ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (r - l == 1) {
            mn[i] = 0;
            cnt[i] = 1;
            return;
        }
        ll m = (l + r) / 2;
        init(2 * i, l, m);
        init(2 * i + 1, m, r);
        mn[i] = 0;
        cnt[i] = cnt[2 * i] + cnt[2 * i + 1];
    }
    void push(ll i, ll l, ll r) {
        if (lazy[i] == 0) return;
        mn[i] += lazy[i];
        if (r - l > 1) {
            lazy[2 * i] += lazy[i];
            lazy[2 * i + 1] += lazy[i];
        }
        lazy[i] = 0;
    }
    void update(ll ul, ll ur, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n;
        push(i, l, r);
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            lazy[i] += val;
            push(i, l, r);
            return;
        }
        ll m = (l + r) / 2;
        update(ul, ur, val, 2 * i, l, m);
        update(ul, ur, val, 2 * i + 1, m, r);
        mn[i] = min(mn[2 * i], mn[2 * i + 1]);
        if (mn[2 * i] == mn[2 * i + 1]) cnt[i] = cnt[2 * i] + cnt[2 * i + 1];
        else if (mn[2 * i] < mn[2 * i + 1]) cnt[i] = cnt[2 * i];
        else cnt[i] = cnt[2 * i + 1];
    }
    pair<ll, ll> query(ll ql, ll qr, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        push(i, l, r);
        if (qr <= l || r <= ql) return {LLONG_MAX, 0};
        if (ql <= l && r <= qr) return {mn[i], cnt[i]};
        ll m = (l + r) / 2;
        auto qlv = query(ql, qr, 2 * i, l, m);
        auto qrv = query(ql, qr, 2 * i + 1, m, r);
        if (qlv.first == qrv.first) return {qlv.first, qlv.second + qrv.second};
        else if (qlv.first < qrv.first) return qlv;
        else return qrv;
    }
    void print(ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        cout << "[" << l << ", " << r << "): " << mn[i] << " " << lazy[i] << '\n';
        if (r - l > 1) {
            ll m = (l + r) / 2;
            print(2 * i, l, m);
            print(2 * i + 1, m, r);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll n, dim=1e6;
    cin >> n;
    // y: <add?, x1, x2>
    map<ll, vector<tuple<bool, ll, ll>>> events;
    FOR (i, n) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += dim, y1 += dim, x2 += dim, y2 += dim;
        events[y1].pb({true, x1, x2});
        events[y2].pb({false, x1, x2});
    }
    SegTree st(2 * dim + 1);
    ll rv = 0, prev_y = 0;
    FORE (e, events) {
        ll y = e.first;
        ll dy = y - prev_y, x0 = st.query(0, 2 * dim + 1).second;
        rv += dy * (2 * dim - x0 + 1);
        prev_y = y;
        for (auto [add, x1, x2] : e.second) {
            if (add) st.update(x1, x2, 1);
            else st.update(x1, x2, -1);
        }
    }
    cout << rv << '\n';

    return 0;
}