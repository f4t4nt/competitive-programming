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
    vector<ll> data, lazy;
    SegTree (ll n) : n(n), data(4 * n), lazy(4 * n) {}
    void push(ll i, ll l, ll r) {
        if (lazy[i] == 0) return;
        data[i] += (r - l) * lazy[i];
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
        cerr << "[" << l << ", " << r << "): " << data[i] << '\n';
        if (r - l > 1) {
            ll m = (l + r) / 2;
            print(2 * i, l, m);
            print(2 * i + 1, m, r);
        }
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;
        // <y, x, color>
        vector<vector<ll>> pts(n, vector<ll>(3));
        map<ll, ll> x_map, y_map, c_map;
        FOR (i, n) {
            cin >> pts[i][1] >> pts[i][0] >> pts[i][2];
            x_map[pts[i][1]] = 0;
            y_map[pts[i][0]] = 0;
            c_map[pts[i][2]] = 0;
        }
        x_map[0] = 0, x_map[1e9 + 1] = 0;
        ll x_cnt = 0, y_cnt = 0, c_cnt = 0;
        FORE (x, x_map) x.second = x_cnt++;
        FORE (y, y_map) y.second = y_cnt++;
        FORE (c, c_map) c.second = c_cnt++;
        map<ll, vector<pair<ll, ll>>> y_range;
        FOR (i, n) {
            pts[i][0] = y_map[pts[i][0]];
            pts[i][1] = x_map[pts[i][1]];
            pts[i][2] = c_map[pts[i][2]];
            y_range[pts[i][0]].pb({pts[i][1], pts[i][2]});
        }
        ssort(pts);
        vector<set<ll>> color_xs(c_cnt, {0, x_cnt});
        SegTree st(x_cnt);
        ll rv = 0;
        for (auto [y, range] : y_range) {
            for (auto [x, c] : range) {
                auto r = color_xs[c].lower_bound(x);
                auto l = r;
                if (l != color_xs[c].begin()) l--;
                if (*l + 1 <= *r - 1) rv = max(rv, st.query(*l + 1, *r));
            }
            vector<pair<ll, ll>> its;
            for (auto [x, c] : range) {
                color_xs[c].insert(x);
                its.pb({x, c});
                st.update(x, x + 1, 1);
            }
            // st.print();
            // cerr << '\n';
        }
        FORE (xs, color_xs) {
            auto l = xs.begin(), r = next(l);
            while (r != xs.end()) {
                rv = max(rv, st.query(*l + 1, *r));
                l = r++;
            }
        }
        cout << rv << '\n';
    }

    return 0;
}