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

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

template<class T>
struct Fenwick {
    ll n;               // logical length (0-indexed externally)
    vector<T> bit;      // 1-based internal tree
    T def_val;          // neutral (usually 0 for +)

    // helpers
    static void combine(T &a, const T &b) { a += b; }               // point-update
    static T    prefix_op(const T &a, const T &b) { return a + b; } // query merge
    static T    inverse (const T &x) { return -x; }                 // for range

    // constructor
    Fenwick(ll _n,
            T _def_val = T{})                   // neutral element
        : n(_n),
          bit(n + 1, _def_val),
          def_val(_def_val) {}

    // point add (a[i] += delta)
    void upd(ll idx, const T &delta) {          // 0-based idx
        for (idx++; idx <= n; idx += idx & -idx)
            combine(bit[idx], delta);
    }

    // prefix sum (inclusive)
    T pref(ll idx) const {                      // 0-based idx
        T res = def_val;
        for (idx++; idx > 0; idx -= idx & -idx)
            res = prefix_op(res, bit[idx]);
        return res;
    }

    // range query [l, r] (inclusive)
    T qry(ll l, ll r) const {
        if (l > r) return def_val;
        return prefix_op(pref(r),
               prefix_op(inverse(pref(l - 1)), def_val));
    }
};

struct Query {
    ll val, l, r, idx, sign;
    bool operator<(const Query &other) const {
        return val < other.val;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, q; cin >> n >> q;
    Fenwick<ll> bit(n);
    vector<pll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i].f;
        a[i].s = i;
    }
    ssort(a);
    vector<ll> ans(q);
    vector<Query> queries(2 * q);
    for (ll i = 0; i < q; i++) {
        ll l, r, mn, mx; cin >> l >> r >> mn >> mx;
        l--, r--;
        queries[i] = {mn - 1, l, r, i, -1};
        queries[i + q] = {mx, l, r, i, 1};
    }
    ll i = 0;
    ssort(queries);
    for (auto &query : queries) {
        while (i < n && a[i].f <= query.val) {
            bit.upd(a[i].s, 1);
            i++;
        }
        ll cnt = bit.qry(query.l, query.r);
        ans[query.idx] += query.sign * cnt;
    }
    for (ll x : ans) cout << x << '\n';

    return 0;
}
