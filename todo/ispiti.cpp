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

// https://open.kattis.com/problems/ispiti

struct SegTree {
    ll n;
    vector<ll> data;
    SegTree (ll n) : n(n), data(4 * n, -1) {}
    void update(ll ul, ll ur, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n;
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            data[i] = val;
            return;
        }
        ll m = (l + r) / 2;
        update(ul, ur, val, 2 * i, l, m);
        update(ul, ur, val, 2 * i + 1, m, r);
        data[i] = max(data[2 * i], data[2 * i + 1]);
    }
    ll query(ll ql, ll qr, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return data[i];
        ll m = (l + r) / 2;
        return max(query(ql, qr, 2 * i, l, m), query(ql, qr, 2 * i + 1, m, r));
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    map<pair<ll, ll>, ll> ref, ref2;
    vector<vector<ll>> qs;
    FOR (i, n) {
        ch t;
        cin >> t;
        if (t == 'D') {
            ll a, b;
            cin >> a >> b;
            qs.pb({0, a, b});
            ref[{b, a}] = 0;
        } else {
            ll a;
            cin >> a;
            qs.pb({1, a});
        }
    }
    ll cnt = 0;
    FORE (i, ref) {x
        i.second = cnt++;
    }
    cnt = 0;
    FORE (q, qs) {
        if (q[0] == 0) {
            q[2] = ref[{q[2], q[1]}];
            ref2[{q[1], q[2]}] = cnt++;
        }
    }
    SegTree st(sz(ref));
    FORE (q, qs) {
        if (q[0] == 0) {
            st.update(q[2], q[2] + 1, q[1]);
        } else {
            ll i = 1, l = 0, r = sz(ref);
            // find 
        }
    }

    return 0;
}