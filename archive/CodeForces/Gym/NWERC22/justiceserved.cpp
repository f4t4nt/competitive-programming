#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define x first
#define y second
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

// struct BIT {
//     vector<ll> tree; ll n;
//     BIT(ll n) : n(n) { tree.resize(n + 1); }
//     void update(ll idx, ll val) {
//         idx++;
//         while (idx <= n) {
//             tree[idx] += val;
//             idx += idx & (-idx);
//         }
//     }
//     ll query(ll idx) {
//         idx++; ll sum = 0;
//         while (idx > 0) {
//             sum += tree[idx];
//             idx -= idx & (-idx);
//         }
//         return sum;
//     }
//     ll query(ll l, ll r) {
//         return query(r) - query(l - 1);
//     }
// };

struct SegTree {
    ll n; vector<ll> data;
    SegTree (ll n) : n(n), data(4 * n) {}
    void upd(ll ul, ll ur, ll val, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            data[i] = val;
            return;
        }
        ll m = (l + r) / 2;
        upd(ul, ur, val, 2 * i, l, m);
        upd(ul, ur, val, 2 * i + 1, m, r);
        data[i] = max(data[2 * i], data[2 * i + 1]);
    }
    ll qry(ll ql, ll qr, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return data[i];
        ll m = (l + r) / 2;
        return max(qry(ql, qr, 2 * i, l, m), qry(ql, qr, 2 * i + 1, m, r));
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    map<ll, ll> t_map;
    vector<pll> times(n);
    FOR (i, n) {
        cin >> times[i].x >> times[i].y;
        times[i].y += times[i].x;
        t_map[times[i].x] = t_map[times[i].y] = 0;
    }
    ll tid = 0;
    for (auto &kv : t_map) kv.y = tid++;
    map<pll, ll> ids;
    FOR (i, n) {
        times[i] = {t_map[times[i].x], t_map[times[i].y]};
        ids[times[i]] = i;
    }
    sort(all(times), [](pll a, pll b) {
        return a.x < b.x || (a.x == b.x && a.y > b.y);
    });
    // BIT bit(tid);
    SegTree st(tid);
    vector<ll> rv(n);
    for (auto [tx, ty] : times) {
        ll i = ids[{tx, ty}];
        // ll val = bit.query(ty, tid - 1);
        ll val = st.qry(ty, tid);
        rv[i] = val;
        // bit.update(ty, 1);
        st.upd(ty, ty + 1, val + 1);
    }
    FOR (i, n) cout << rv[i] << ' ';
    cout << '\n';

    return 0;
}