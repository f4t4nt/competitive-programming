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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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
    // sum, pref, suff
    // sum[i] = sum[i * 2] + sum[i * 2 + 1]
    // pref[i] = pref[i * 2] + sum[i * 2 + 1]
    // suff[i] = suff[i * 2 + 1] + sum[i * 2]
    // data[i] = max(data[i * 2], data[i * 2 + 1], suff[i * 2] + pref[i * 2 + 1])
    vector<ll> data, sum, pref, suff;
    SegTree (ll n) : n(n), data(4 * n), sum(4 * n), pref(4 * n), suff(4 * n) {}
    void update(ll ui, ll val, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (ui == l && ui == r - 1) {
            data[i] = val;
            sum[i] = val;
            pref[i] = val;
            suff[i] = val;
            return;
        }
        ll m = (l + r) / 2;
        if (ui < m) update(ui, val, 2 * i, l, m);
        else update(ui, val, 2 * i + 1, m, r);
        sum[i] = sum[2 * i] + sum[2 * i + 1];
        pref[i] = max(pref[2 * i], sum[2 * i] + pref[2 * i + 1]);
        suff[i] = max(suff[2 * i + 1], suff[2 * i] + sum[2 * i + 1]);
        data[i] = max({data[2 * i], data[2 * i + 1], suff[2 * i] + pref[2 * i + 1], 0LL});
    }
    ll query() {
        return data[1];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, q;
    cin >> n >> q;
    SegTree st(n);
    FOR (i, n) {
        ll a;
        cin >> a;
        st.update(i, a);
    }
    while (q--) {
        ll i, v;
        cin >> i >> v;
        st.update(i - 1, v);
        cout << st.query() << '\n';
    }

    return 0;
}