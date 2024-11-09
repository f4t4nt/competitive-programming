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
    ll,
    null_type,
    less<ll>,
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
// #define x first
// #define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x <= (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

struct BIT {
    vector<ll> tree; ll n;
    BIT(ll n) : n(n) { tree.resize(n + 1); }
    void update(ll idx, ll val) {
        idx++;
        while (idx <= n)
        { tree[idx] += val; idx += idx & (-idx); }
    }
    ll query(ll idx) {
        idx++; ll sum = 0;
        while (idx > 0)
        { sum += tree[idx]; idx -= idx & (-idx); }
        return sum;
    }
    ll query(ll l, ll r) { return query(r) - query(l - 1); }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, q; cin >> n >> q;
    vector<ll> a(n), pre(n + 1), ans(q);
    BIT bit(n);
    FOR (i, n) {
        cin >> a[i];
        pre[i + 1] = pre[i] + a[i];
    }
    vector<tuple<ll, ll, ll>> queries(q);
    FOR (i, q) {
        ll l, r; cin >> l >> r;
        l--, r--;
        queries[i] = { l, r, i };
    }
    rsort(queries);
    vector<pll> stk;
    vector<ll> ref(n);
    set<ll> active;
    ll i = n - 1;
    for (auto [l, r, idx] : queries) {
        while (i >= l) {
            while (sz(stk) && stk.back().first <= a[i]) {
                ll j = stk.back().second;
                bit.update(j, -ref[j]);
                ref[j] = 0;
                active.erase(j);
                stk.pop_back();
            }
            ll j = n;
            if (sz(stk)) j = stk.back().second;
            active.insert(i);
            ref[i] = (j - i) * a[i] - pre[j] + pre[i];
            bit.update(i, ref[i]);
            stk.pb({a[i], i});
            i--;
        }
        auto it = active.upper_bound(r);
        ll prv = n - 1, &res = ans[idx];
        if (it != active.begin()) {
            it--;
            prv = *it;
            res += bit.query(i, prv - 1);
        }
        res += (r + 1 - prv) * a[prv] - pre[r + 1] + pre[prv];
    }
    for (ll res : ans) cout << res << '\n';

    return 0;
}