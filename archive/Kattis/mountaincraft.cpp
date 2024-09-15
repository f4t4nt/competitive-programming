#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
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
#define f first
#define s second

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

struct SegTree {
    // <length (immutable), total length at min (mutable), count (mutable)>
    ll n, tot; vector<tuple<ll, ll, ll>> data; vector<ll> lazy;
    SegTree (ll n, vector<ll> &raw) : n(n), data(4 * n), lazy(4 * n)
        { build(raw); tot = accumulate(all(raw), 0ll); }
    tuple<ll, ll, ll> build(vector<ll> &raw, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (r - l == 1) return data[i] = {raw[l], raw[l], 0};
        ll m = (l + r) / 2;
        auto [lf, ls, lc] = build(raw, 2 * i, l, m);
        auto [rf, rs, rc] = build(raw, 2 * i + 1, m, r);
        return data[i] = {lf + rf, lf + rf, 0};
    }
    void push(ll i, ll l, ll r) {
        get<2>(data[i]) += lazy[i];
        if (r - l > 1) {
            lazy[2 * i] += lazy[i];
            lazy[2 * i + 1] += lazy[i];
        }
        lazy[i] = 0;
    }
    void upd(ll ul, ll ur, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n; push(i, l, r);
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            lazy[i] += val;
            push(i, l, r);
            return;
        }
        ll m = (l + r) / 2;
        upd(ul, ur, val, 2 * i, l, m);
        upd(ul, ur, val, 2 * i + 1, m, r);
        auto [lf, ls, lc] = data[2 * i];
        auto [rf, rs, rc] = data[2 * i + 1];
        assert(ls != 0 && rs != 0);
        if (lc < rc) data[i] = {lf + rf, ls, lc};
        elif (lc > rc) data[i] = {lf + rf, rs, rc};
        else data[i] = {lf + rf, ls + rs, lc};
    }
    ll qry() {
        if (get<2>(data[1])) return 0;
        return tot - get<1>(data[1]);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ld sqrt2 = sqrtl(2);

    ll q, w; cin >> q >> w;
    map<ll, ll> pos;
    pos[0] = pos[w + 1] = 0;
    vector<pll> segs;
    FOR (i, q) {
        ll x, y; cin >> x >> y;
        ll l = x - y, r = x + y;
        segs.pb({l, r});
        pos[max(l, 0ll)] = pos[min(r, w)] = 0;
    }

    ll cnt = 0, prv = -1;
    vector<ll> raw;
    FORE (p, pos) {
        p.s = cnt++;
        raw.pb(p.f - prv);
        prv = p.f;
    }

    SegTree st(sz(raw), raw);
    set<pll> active;
    for (auto [l, r] : segs) {
        ll l0 = pos[max(l, 0ll)] + 1, r0 = pos[min(r, w)] + 1;
        if (active.count({l, r})) {
            active.erase({l, r});
            st.upd(l0, r0, -1);
        } else {
            active.insert({l, r});
            st.upd(l0, r0, 1);
        }
        cout << fixed << setprecision(18) << st.qry() * sqrt2 << '\n';
    }

    return 0;
}