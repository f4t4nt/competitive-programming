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

struct SegTree {
    ll n;               // logical length
    ll N;               // next power of 2 of n
    vector<tuple<ll, ll, ll, ll>> data;     // segment values
    vector<ll> lazy;     // lazy tags
    tuple<ll, ll, ll, ll> def_val;          // neutral for combine
    ll def_tag;          // neutral for compose

    // helpers
    static ll next_pow2(ll x) {
        return x <= 1 ? 1 : 1LL << (64 - __builtin_clzll(x - 1));
    }

    static tuple<ll, ll, ll, ll> combine(const tuple<ll, ll, ll, ll> &a, const tuple<ll, ll, ll, ll> &b) {
        return {
            get<0>(a) + get<0>(b),
            max(get<1>(a), get<0>(a) + get<1>(b)),
            max(get<2>(b), get<2>(a) + get<0>(b)),
            max({get<3>(a), get<3>(b), get<2>(a) + get<1>(b)})
        };
    }

    // constructors
    SegTree(ll _n,
            const vector<tuple<ll, ll, ll, ll>> &raw = {},
            tuple<ll, ll, ll, ll> _def_val = tuple<ll, ll, ll, ll>{},       // neutral for combine (e.g. +inf for min)
            ll _def_tag = ll{})       // neutral for lazy tag   (usually 0)
        : n(_n), N(next_pow2(_n)),
          data(2 * N, _def_val),
          lazy(2 * N, _def_tag),
          def_val(_def_val),
          def_tag(_def_tag)
    {
        if (!raw.empty())
            build(const_cast<vector<tuple<ll, ll, ll, ll>>&>(raw));
    }

    // build / fill
    tuple<ll, ll, ll, ll> build(vector<tuple<ll, ll, ll, ll>> &raw, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = N;
        if (r - l == 1) return data[i] = (l < n ? raw[l] : def_val);
        ll m = (l + r) / 2;
        data[i] = combine(
            build(raw, 2 * i, l, m),
            build(raw, 2 * i + 1, m, r)
        );
        return data[i];
    }

    // range query [ql, qr)
    tuple<ll, ll, ll, ll> qry(ll ql, ll qr,
          ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = N;
        if (qr <= l || r <= ql) return def_val;
        if (ql <= l && r <= qr) return data[i];
        ll m = (l + r) / 2;
        return combine(
            qry(ql, qr, 2 * i, l, m),
            qry(ql, qr, 2 * i + 1, m, r)
        );
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, q; cin >> n >> q;
    vector<tuple<ll, ll, ll, ll>> a(n);
    for (ll i = 0; i < n; i++) {
        ll x; cin >> x;
        if (x > 0) a[i] = {x, x, x, x};
        else a[i] = {x, 0, 0, 0};
    }
    SegTree st(n, a, {0, 0, 0, 0}, 0);
    while (q--) {
        ll l, r; cin >> l >> r;
        l--, r--;
        auto [sum, pre, suf, mx] = st.qry(l, r + 1);
        cout << mx << '\n';
    }

    return 0;
}
