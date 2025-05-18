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
    ll n; vector<ll> data, sum, pre, suf;
    SegTree (ll n) : n(n), data(4 * n), sum(4 * n), pre(4 * n), suf(4 * n) {}
    void upd(ll ui, ll val, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (ui == l && ui == r - 1) {
            data[i] = max(val, 0LL);
            sum[i] = val;
            pre[i] = val;
            suf[i] = val;
            return;
        }
        ll m = (l + r) / 2;
        if (ui < m) upd(ui, val, 2 * i, l, m);
        else upd(ui, val, 2 * i + 1, m, r);
        sum[i] = sum[2 * i] + sum[2 * i + 1];
        pre[i] = max(pre[2 * i], sum[2 * i] + pre[2 * i + 1]);
        suf[i] = max(suf[2 * i + 1], suf[2 * i] + sum[2 * i + 1]);
        data[i] = max({data[2 * i], data[2 * i + 1], suf[2 * i] + pre[2 * i + 1], 0LL});
    }
    ll qry() { return data[1]; }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q; cin >> n >> q;
    vector<ll> raw(n);
    FOR (i, n) cin >> raw[i];
    SegTree st(n);
    FOR (i, n) st.upd(i, raw[i]);
    while (q--) {
        ll i, v; cin >> i >> v;
        st.upd(--i, v);
        cout << st.qry() << '\n';
    }

    return 0;
}