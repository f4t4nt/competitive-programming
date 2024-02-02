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

#define f first
#define s second

ll sum(ll n) { return n * (n + 1) / 2; }

struct SegTree {
    ll n; vector<ll> data;
    vector<pll> lazy;
    SegTree (ll n, vector<ll> &raw) : n(n), data(4 * n), lazy(4 * n)
        { build(raw); }
    ll build(vector<ll> &raw, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (r - l == 1) return data[i] = raw[l];
        ll m = (l + r) / 2;
        return data[i] = build(raw, 2 * i, l, m) + build(raw, 2 * i + 1, m, r);
    }
    void push(ll i, ll l, ll r) {
        if (r - l > 1) {
            ll m = (l + r) / 2;
            lazy[2 * i].f += lazy[i].f;
            lazy[2 * i + 1].f += lazy[i].f + (m - l) * lazy[i].s;
            lazy[2 * i].s += lazy[i].s;
            lazy[2 * i + 1].s += lazy[i].s;
            data[2 * i] += sum(m - l) * lazy[i].s + (m - l) * lazy[i].f;
            data[2 * i + 1] += sum(r - m) * lazy[i].s + (r - m) * (lazy[i].f + (m - l) * lazy[i].s);
        }
        lazy[i] = {0, 0};
    }
    void upd(ll ul, ll ur, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n;
        push(i, l, r);
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            data[i] += sum(r - l) + (l - ul) * (r - l);
            lazy[i].f += l - ul;
            lazy[i].s++;
            return;
        }
        ll m = (l + r) / 2;
        upd(ul, ur, val, 2 * i, l, m);
        upd(ul, ur, val, 2 * i + 1, m, r);
        data[i] = data[2 * i] + data[2 * i + 1];
    }
    ll qry(ll ql, ll qr, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        push(i, l, r);
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return data[i];
        ll m = (l + r) / 2;
        return qry(ql, qr, 2 * i, l, m) + qry(ql, qr, 2 * i + 1, m, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q; cin >> n >> q;
    vector<ll> raw(n);
    FOR (i, n) cin >> raw[i];
    SegTree st(n, raw);
    while (q--) {
        ll t, a, b; cin >> t >> a >> b; a--;
        if (t == 1) st.upd(a, b, 1);
        else cout << st.qry(a, b) << '\n';
    }

    return 0;
}