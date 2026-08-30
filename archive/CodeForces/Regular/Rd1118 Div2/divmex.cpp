#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
// s.order_of_key(x) -> number of elements < x
// s.find_by_order(x) -> iterator to the x-th element (0-indexed)

#pragma GCC target("popcnt,lzcnt")
// __builtin_popcount(x) -> number of set bits
// __builtin_clz(x) -> number of leading zeros
// for ll, use __builtin_popcountll, __builtin_clzll

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

// qry(i) = min r s.t. [i,r] covers all prime powers so far, so a segment free of q_t works iff qry(L) <= R

ll spf[200005], pid[400005], seg[800005];
vector<ll> pws;
vector<vector<ll>> occ;

void build(ll v, ll tl, ll tr) {
    if (tl == tr) {
        seg[v] = tl;
        return;
    }
    seg[v] = 0;
    ll tm = (tl + tr) / 2;
    build(2 * v, tl, tm), build(2 * v + 1, tm + 1, tr);
}

void upd(ll v, ll tl, ll tr, ll l, ll r, ll x) {
    if (r < tl || tr < l) return;
    if (l <= tl && tr <= r) {
        seg[v] = max(seg[v], x);
        return;
    }
    ll tm = (tl + tr) / 2;
    upd(2 * v, tl, tm, l, r, x), upd(2 * v + 1, tm + 1, tr, l, r, x);
}

ll qry(ll v, ll tl, ll tr, ll i) {
    if (tl == tr) return seg[v];
    ll tm = (tl + tr) / 2;
    if (i <= tm) return max(seg[v], qry(2 * v, tl, tm, i));
    return max(seg[v], qry(2 * v + 1, tm + 1, tr, i));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll mx = 200000, mx2 = 400000;
    for (ll i = 2; i <= mx; i++)
        if (!spf[i])
            for (ll j = i; j <= mx; j += i)
                if (!spf[j]) spf[j] = i;

    vector<bool> comp(mx2 + 1);
    for (ll i = 2; i <= mx2; i++)
        if (!comp[i])
            for (ll j = 2 * i; j <= mx2; j += i) comp[j] = 1;

    for (ll p = 2; p <= mx2; p++)
        if (!comp[p])
            for (ll q = p; q <= mx2; q *= p) pws.pb(q);
    ssort(pws);
    for (ll i = 0; i < sz(pws); i++) pid[pws[i]] = i;
    occ.resize(sz(pws));

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> a(n + 1);
        for (ll i = 1; i <= n; i++) cin >> a[i];

        vector<ll> touched;
        for (ll i = 1; i <= n; i++) {
            ll x = a[i];
            while (x > 1) {
                ll p = spf[x], q = 1;
                while (x % p == 0) {
                    x /= p, q *= p;
                    if (occ[pid[q]].empty()) touched.pb(pid[q]);
                    occ[pid[q]].pb(i);
                }
            }
        }

        build(1, 1, n);
        vector<ll> ans;
        for (ll idx = 0; idx < sz(pws); idx++) {
            vector<ll>& ps = occ[idx];
            if (ps.empty()) {
                if (qry(1, 1, n, 1) <= n) ans.pb(pws[idx]);
                break;
            }
            bool ok = false;
            ll prv = 0;
            for (ll j = 0; j <= sz(ps); j++) {
                ll cur = j < sz(ps) ? ps[j] : n + 1;
                if (prv + 1 <= cur - 1 && !ok && qry(1, 1, n, prv + 1) <= cur - 1) ok = 1;
                prv = cur;
            }
            if (ok) ans.pb(pws[idx]);
            prv = 0;
            for (ll j = 0; j < sz(ps); j++) {
                upd(1, 1, n, prv + 1, ps[j], ps[j]);
                prv = ps[j];
            }
            if (prv < n) upd(1, 1, n, prv + 1, n, n + 1);
        }

        cout << sz(ans) << '\n';
        for (ll i = 0; i < sz(ans); i++) cout << ans[i] << ' ';
        cout << '\n';
        for (ll id : touched) occ[id].clear();
    }

    return 0;
}
