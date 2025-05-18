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

template<class T, class U = T>
struct PersistentSegTree {
    // helpers
    // combine two child node values
    static inline T combine(const T &a, const T &b) { return a + b; }

    // apply a poll update tag to a leaf value (len == 1 always)
    static inline void apply (T &leaf, const U &tag) { leaf += tag; }

    // node structure
    struct Node {
        ll l, r;        // child indices in pool
        T  val;         // aggregate value for that segment
        Node(ll _l = -1, ll _r = -1, const T &_v = T{}) : l(_l), r(_r), val(_v) {}
    };

    int          n;         // logical length [0..n-1]
    int          nxt = 0;   // next unused index in pool
    vector<Node> pool;      // node arena
    vector<int>  root;      // version -> root idx

    // constructor
    explicit PersistentSegTree(int _n, const vector<T> &raw = {})
        : n(_n)
    {
        pool.resize(20 * n);
        nxt = 0;
        if (!raw.empty()) build(const_cast<vector<T>&>(raw));
        else build(vector<T>(n, T{}));
    }

    // build from raw array O(n)
    int build(const vector<T> &a) {
        root.clear();
        root.pb(build(0, n - 1, a));
        return 0;
    }

    // fill raw array from segment tree
    void fill(vector<T> &vec, int vid) {
        assert(sz(vec) == n);
        fill(vec, root[vid], 0, n - 1);
    }

    // point update
    int upd(int vid, int ui, const U &delta) {
        int new_root = upd(root[vid], 0, n - 1, ui, delta);
        root.pb(new_root);
        return sz(root) - 1;
    }

    // range query [ql, qr] inclusive O(log n)
    T qry(int vid, int l, int r) const {
        return qry(root[vid], 0, n - 1, l, r);
    }

    // informational helpers
    int versions() const { return sz(root); }

private:
    inline int make(int L, int R, const T &val) {
        if (nxt >= sz(pool)) pool.resize(sz(pool) * 2);
        pool[nxt] = {L, R, val};
        return nxt++;
    }

    int build(int l, int r, const vector<T> &a) {
        if (l == r) return make(0, 0, a.empty() ? T{} : a[l]);
        int m = (l + r) / 2;
        int L = build(l, m, a);
        int R = build(m + 1, r, a);
        return make(L, R, combine(pool[L].val, pool[R].val));
    }

    void fill(vector<T> &vec, int v, int l, int r) {
        if (l == r) {
            if (l < n) vec[l] = pool[v].val;
            return;
        }
        int m = (l + r) / 2;
        fill(vec, pool[v].l, l, m);
        fill(vec, pool[v].r, m + 1, r);
    }

    int upd(int v, int l, int r, int ui, const U &delta) {
        if (l == r) {
            T nv = pool[v].val;
            apply(nv, delta);
            return make(0, 0, nv);
        }
        int m = (l + r) >> 1;
        int L = pool[v].l;
        int R = pool[v].r;
        if (ui <= m) L = upd(L, l, m, ui, delta);
        else         R = upd(R, m + 1, r, ui, delta);
        return make(L, R, combine(pool[L].val, pool[R].val));
    }

    T qry(int v, int l, int r, int ql, int qr) const {
        if (ql > qr) return T{};
        if (ql == l && qr == r) return pool[v].val;
        int m = (l + r) / 2;
        return combine(
            qry(pool[v].l, l, m, ql, min(qr, m)),
            qry(pool[v].r, m + 1, r, max(ql, m + 1), qr)
        );
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, q; cin >> n >> q;
    vector<ll> a(n);
    for (ll &x : a) cin >> x;
    auto comp = a;
    ssort(comp);
    comp.erase(unique(all(comp)), comp.end());
    ll m = sz(comp);
    auto idx = [&](ll x) {
        return (upper_bound(all(comp), x) - comp.begin()) - 1;
    };
    PersistentSegTree<ll> pst(m);
    vector<ll> ver(n + 1);
    for (ll i = 0; i < n; i++)
        ver[i + 1] = pst.upd(ver[i], idx(a[i]), a[i]);
    vector<vector<ll>> tmp(n + 1, vector<ll>(m));
    for (ll i = 0; i <= n; i++)
        pst.fill(tmp[i], ver[i]);
    while (q--) {
        ll l, r; cin >> l >> r; l--;
        ll ans = 1;
        while (true) {
            ll pos = idx(ans);
            if (pos < 0) break;
            ll sum = pst.qry(ver[r], 0, pos) - pst.qry(ver[l], 0, pos);
            if (sum < ans) break;
            ans = sum + 1;
        }
        cout << ans << '\n';
    }

    return 0;
}
