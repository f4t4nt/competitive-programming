#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// -----------------------------------------------------------------------------
//  Dynamic SegTree (sum, point add)
// -----------------------------------------------------------------------------
//  Supports:   - add(i, x)   point add at index i
//              - qry(l, r)   sum over [l, r] inclusive
//  Complexity:  O(log range) per op; memory O(updates * log range)
//  Notes:      - nodes are made on first touch, so the index range can be
//                huge (1e18-ish) with no coordinate compression
//              - for versioned roots over a dense array see persistent_segtree.h
// -----------------------------------------------------------------------------
struct DynamicSegTree {
    struct Node {
        ll sum = 0;                         // aggregate over the node's range
        Node *lc = nullptr, *rc = nullptr;  // children, null until touched
    };

    ll lo, hi;      // whole index range [lo, hi]
    Node *root;

    DynamicSegTree(ll _lo, ll _hi) : lo(_lo), hi(_hi), root(new Node()) {}

    void add(ll i, ll x) { add(root, lo, hi, i, x); }

    ll qry(ll l, ll r) const { return qry(root, lo, hi, l, r); }

private:
    void add(Node *v, ll l, ll r, ll i, ll x) {
        v->sum += x;
        if (l == r) return;
        ll m = l + (r - l) / 2;
        if (i <= m) {
            if (!v->lc) v->lc = new Node();
            add(v->lc, l, m, i, x);
        } else {
            if (!v->rc) v->rc = new Node();
            add(v->rc, m + 1, r, i, x);
        }
    }

    ll qry(Node *v, ll l, ll r, ll ql, ll qr) const {
        if (!v || qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return v->sum;
        ll m = l + (r - l) / 2;
        return qry(v->lc, l, m, ql, qr) + qry(v->rc, m + 1, r, ql, qr);
    }
};
