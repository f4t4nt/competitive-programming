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
    ll n; vector<ll> data, lens;
    vector<bool> active, lazy;
    SegTree (ll n, vector<ll> &raw) : n(n), data(4 * n), lens(4 * n), active(4 * n), lazy(4 * n)
        { build(raw); }
    ll build(vector<ll> &raw, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (r - l == 1) return lens[i] = raw[l];
        ll m = (l + r) / 2;
        return lens[i] = build(raw, 2 * i, l, m) + build(raw, 2 * i + 1, m, r);
    }
    void push(ll i, ll l, ll r) {
        if (lazy[i]) {
            data[i] = lens[i] - data[i];
            if (r - l > 1) {
                lazy[2 * i] = !lazy[2 * i];
                lazy[2 * i + 1] = !lazy[2 * i + 1];
            }
            lazy[i] = false;
        }
    }
    void upd(ll ul, ll ur, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n; push(i, l, r);
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            lazy[i] = true;
            push(i, l, r);
            return;
        }
        ll m = (l + r) / 2;
        upd(ul, ur, 2 * i, l, m);
        upd(ul, ur, 2 * i + 1, m, r);
        data[i] = data[2 * i] + data[2 * i + 1];
    }
    ll qry() {
        push(1, 0, n);
        return data[1];
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    map<ll, ll> y_map;
    map<ll, vector<pll>> events;
    FOR (i, n) {
        ll x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        y_map[y1] = y_map[y2] = 0;
        if (y1 > y2) swap(y1, y2);
        events[x1].pb({y1, y2});
        events[x2].pb({y1, y2});
    }
    vector<ll> lens;
    ll prev_y = 0, cnt = 0;
    FORE (y, y_map) {
        y.s = ++cnt;
        lens.pb(y.f - prev_y);
        prev_y = y.f;
    }
    SegTree st(sz(lens), lens);
    FORE (event, events) {
        FORE (y, event.s) {
            y = {y_map[y.f], y_map[y.s]};
        }
    }
    ll active = 0, prev_x = 0, ans = 0;
    FORE (event, events) {
        ans += st.qry() * (event.f - prev_x);
        prev_x = event.f;
        FORE (y, event.s) {
            st.upd(y.f, y.s);
        }
    }
    cout << ans << '\n';

    return 0;
}