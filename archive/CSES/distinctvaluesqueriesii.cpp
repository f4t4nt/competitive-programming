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
// #define f first
// #define s second

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
struct SegTree {
    ll n;               // logical length
    ll N;               // next power of 2 of n
    vector<T> data;     // segment values
    T def_val;          // neutral for combine

    // helpers
    static ll next_pow2(ll x) {
        return x <= 1 ? 1 : 1LL << (64 - __builtin_clzll(x - 1));
    }

    static T  combine(const T &a, const T &b)          { return min(a, b); }

    // constructors
    SegTree(ll _n,
            const vector<T> &raw = {},
            T _def_val = T{})       // neutral for combine (e.g. +inf for min)
        : n(_n), N(next_pow2(_n)),
          data(2 * N, _def_val),
          def_val(_def_val)
    {
        if (!raw.empty())
            build(const_cast<vector<T>&>(raw));
    }

    // build / fill
    T build(vector<T> &raw, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = N;
        if (r - l == 1) return data[i] = (l < n ? raw[l] : def_val);
        ll m = (l + r) / 2;
        data[i] = combine(
            build(raw, 2 * i, l, m),
            build(raw, 2 * i + 1, m, r)
        );
        return data[i];
    }

    // point update
    void updi(ll ui, const T &val,
              ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = N;
        if (r - l == 1) { data[i] = val; return; }
        ll m = (l + r) / 2;
        if (ui < m) updi(ui, val, 2 * i, l, m);
        else        updi(ui, val, 2 * i + 1, m, r);
        data[i] = combine(data[2 * i], data[2 * i + 1]);
    }

    // range query [ql, qr)
    T qry(ll ql, ll qr,
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
    vector<ll> a(n);
    map<ll, set<ll>> pos;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].insert(i);
    }
    vector<ll> nxt(n);
    for (ll i = 0; i < n; i++) {
        auto it = pos[a[i]].upper_bound(i);
        if (it == pos[a[i]].end()) nxt[i] = n;
        else nxt[i] = *it;
    }
    SegTree<ll> st(n, nxt, n);
    while (q--) {
        ll t; cin >> t;
        if (t == 1) {
            ll i, x; cin >> i >> x; i--;
            {
                auto &S = pos[a[i]];
                auto it  = S.find(i);
                auto nxt_it = std::next(it);
                auto prv_it = (it == S.begin() ? S.end() : std::prev(it));
                if (prv_it != S.end()) {
                    nxt[*prv_it] = (nxt_it == S.end() ? n : *nxt_it);
                    st.updi(*prv_it, nxt[*prv_it]);
                }
                S.erase(it);
            }
            {
                auto &S = pos[x];
                auto nxt_it = S.lower_bound(i);
                auto prv_it = (nxt_it == S.begin() ? S.end() : std::prev(nxt_it));
                nxt[i] = (nxt_it == S.end() ? n : *nxt_it);
                st.updi(i, nxt[i]);
                if (prv_it != S.end()) {
                    nxt[*prv_it] = i;
                    st.updi(*prv_it, i);
                }
                S.insert(i);
            }
            a[i] = x;
        } else {
            ll l, r; cin >> l >> r; l--;
            ll ans = st.qry(l, r);
            cout << (ans >= r ? "YES\n" : "NO\n");
        }
    }

    return 0;
}
