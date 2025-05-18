#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define pb push_back
#define sz(C) (ll) C.size()

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
