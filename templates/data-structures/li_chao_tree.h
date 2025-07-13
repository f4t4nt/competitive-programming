#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define sz(C) (ll) C.size()
#define pb push_back

const ll INF = 4e18;

// -----------------------------------------------------------------------------
//  Li Chao segment tree - fully‑dynamic convex hull trick
// -----------------------------------------------------------------------------
//  Supports:    - add_line(m, b)   (insert y = mx + b)
//               - query(x)         (min_y at integer x)
//  Complexity:  O(log X) per operation, X = |domain| (coordinate range)
//               Memory ~ (# of inserted lines) nodes
//  Coordinates: define X_MIN, X_MAX when the structure is created
// -----------------------------------------------------------------------------
struct Line {
    ll m, b;    // y = mx + b
    Line(ll _m = 0, ll _b = INF) : m(_m), b(_b) {}
    inline ll val(ll x) const { return m * x + b; }
};

struct LiChao {
    struct Node {
        Line ln;        // line stored in this segment
        Node *l = nullptr, *r = nullptr;
        Node(Line _ln = Line{}) : ln(_ln) {}
    };

    ll X_MIN, X_MAX;    // inclusive domain bounds
    Node *root = nullptr;

    explicit LiChao(ll _L, ll _R) : X_MIN(_L), X_MAX(_R) {
        assert(_L <= _R);
    }

    // insert y = mx + b
    void add_line(ll m, ll b) { add_line(root, X_MIN, X_MAX, Line(m, b)); }

    // insert a pre‑built Line
    void add_line(Line nw) { add_line(root, X_MIN, X_MAX, nw); }

    // query minimum y at integer x
    ll query(ll x) const {
        assert(X_MIN <= x && x <= X_MAX);
        return query(root, X_MIN, X_MAX, x);
    }

private:
    // recursive insertion
    static void add_line(Node *&p, ll l, ll r, Line nw) {
        if (!p) { p = new Node(nw); return; }

        ll mid = (l + r) >> 1;
        bool left  = nw.val(l)  < p->ln.val(l);
        bool miden = nw.val(mid) < p->ln.val(mid);
        if (miden) swap(nw, p->ln);     // keep better line at mid

        if (l == r) return;             // leaf reached
        if (left != miden)
            add_line(p->l, l, mid, nw);
        else
            add_line(p->r, mid + 1, r, nw);
    }

    // recursive query
    static ll query(Node *p, ll l, ll r, ll x) {
        if (!p) return INF;
        ll res = p->ln.val(x);
        if (l == r) return res;
        ll mid = (l + r) >> 1;
        if (x <= mid) return min(res, query(p->l, l, mid, x));
        else          return min(res, query(p->r, mid + 1, r, x));
    }
};
