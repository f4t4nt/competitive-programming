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

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
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

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

template<class T, class U = T>
struct SegTree {
    using ll = long long;

    ll n;                     // logical length
    ll N;                     // next power of 2 of n
    vector<T> data;           // segment values
    vector<U> lazy;           // lazy tags
    T def_val;                // neutral for combine
    U def_tag;                // neutral for compose

    /*-----------  helpers  -----------*/
    static ll next_pow2(ll x) {
        if (x <= 1) return 1;
        --x; for (int s = 1; s < 64; s <<= 1) x |= x >> s;
        return x + 1;
    }

    static T  combine(const T &a, const T &b)          { return min(a, b); }
    static void apply  (T &node, const U &tag, ll len) { node += tag; }
    static void compose(U &dst, const U &src)          { dst += src; }
    /*---------------------------------*/

    /*-----------  ctor  -----------*/
    SegTree(ll _n,
            const vector<T> &raw = {},
            T _def_val = T{},          // neutral for combine (e.g. +inf for min)
            U _def_tag = U{})          // neutral for lazy tag   (usually 0)
        : n(_n), N(next_pow2(_n)),
          data(4 * N, _def_val),
          lazy(4 * N, _def_tag),
          def_val(_def_val),
          def_tag(_def_tag)
    {
        if (!raw.empty()) {
            auto tmp = raw;
            tmp.resize(N, _def_val);
            build(tmp);
        }
    }

    /*-----------  build / export -----------*/
    T build(vector<T> &raw, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = N;
        if (r - l == 1) return data[i] = raw[l];
        ll m = (l + r) / 2;
        data[i] = combine(
            build(raw, 2 * i, l, m),
            build(raw, 2 * i + 1, m, r)
        );
        return data[i];
    }

    void fill(vector<T> &vec, ll i = 1, ll l = 0, ll r = -1) {
        assert(sz(vec) == n);
        if (r == -1) r = N; push(i, l, r);
        if (r - l == 1) { if (l < n) vec[l] = data[i]; }
        else {
            ll m = (l + r) / 2;
            fill(vec, 2 * i, l, m);
            fill(vec, 2 * i + 1, m, r);
        }
    }

    /*-----------  lazy machinery -----------*/
    void push(ll i, ll l, ll r) {
        if (lazy[i] == def_tag) return;
        apply(data[i], lazy[i], r - l);
        if (r - l > 1) {
            compose(lazy[2 * i],     lazy[i]);
            compose(lazy[2 * i + 1], lazy[i]);
        }
        lazy[i] = def_tag;
    }

    /*-----------  range update -----------*/
    void upd(ll ul, ll ur, const U &val,
             ll i = 1, ll l = 0, ll r = -1) {   // [ul, ur)
        if (r == -1) r = N; push(i, l, r);
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            compose(lazy[i], val); push(i, l, r); return;
        }
        ll m = (l + r) / 2;
        upd(ul, ur, val, 2 * i, l, m);
        upd(ul, ur, val, 2 * i + 1, m, r);
        data[i] = combine(data[2 * i], data[2 * i + 1]);
    }

    /*-----------  point assign -----------*/
    void updi(ll ui, const T &val,
              ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = N; push(i, l, r);
        if (r - l == 1) { data[i] = val; return; }
        ll m = (l + r) / 2;
        if (ui < m) updi(ui, val, 2 * i, l, m);
        else        updi(ui, val, 2 * i + 1, m, r);
        data[i] = combine(data[2 * i], data[2 * i + 1]);
    }

    /*-----------  range query -----------*/
    T qry(ll ql, ll qr,
          ll i = 1, ll l = 0, ll r = -1) {      // [ql, qr)
        if (r == -1) r = N; push(i, l, r);
        if (qr <= l || r <= ql) return def_val;
        if (ql <= l && r <= qr) return data[i];
        ll m = (l + r) / 2;
        return combine(
            qry(ql, qr, 2 * i, l, m),
            qry(ql, qr, 2 * i + 1, m, r)
        );
    }

    /*-----------  point query -----------*/
    T qryi(ll qi, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = N; push(i, l, r);
        if (r - l == 1) return data[i];
        ll m = (l + r) / 2;
        return (qi < m) ? qryi(qi, 2 * i, l, m)
                        : qryi(qi, 2 * i + 1, m, r);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    str line;
    getline(cin, line);
    ll n = stoll(line);
    vector<ll> a(n);
    getline(cin, line);
    istringstream iss(line);
    for (ll &x : a) iss >> x;
    SegTree<ll> st(n, a, 1e18);
    getline(cin, line);
    ll q = stoll(line);
    while (q--) {
        getline(cin, line);
        istringstream iss(line);
        vector<ll> qry;
        ll x;
        while (iss >> x) qry.pb(x);
        
        if (sz(qry) == 2) {
            if (qry[0] <= qry[1]) cout << st.qry(qry[0], qry[1] + 1) << '\n';
            else cout << min(st.qry(qry[0], n), st.qry(0, qry[1] + 1)) << '\n';
        } else {
            if (qry[0] <= qry[1]) st.upd(qry[0], qry[1] + 1, qry[2]);
            else st.upd(qry[0], n, qry[2]), st.upd(0, qry[1] + 1, qry[2]);
        }
    }

    return 0;
}
