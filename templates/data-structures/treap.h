#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define pb push_back

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// -----------------------------------------------------------------------------
//  Implicit Treap
// -----------------------------------------------------------------------------
//  Supports:   - insert(pos, val)  insert val so it ends up at index pos
//              - erase(pos)        remove index pos
//              - reverse(l, r)     reverse [l, r]
//              - qry(l, r)         sum over [l, r]
//              - vals()            in-order contents
//  Restrictions:
//              - 0-based, [l, r] inclusive and non-empty, pos in [0, size()]
//  Complexity:  O(log n) expected per operation
//  Notes:      - sequence by position (no keys), split/merge on subtree sizes
//              - nodes are new'd and never freed
//              - push() before touching children; extend push/pull for new
//                lazies (e.g. range add)
// -----------------------------------------------------------------------------
struct Treap {
    struct Node {
        ll val, priority;   // stored value, heap priority
        ll size = 1, sum;   // subtree size / subtree sum
        bool rev = false;   // lazy reversal flag
        Node *child[2];     // left, right
        Node(ll _val) : val(_val), priority(rng()), sum(_val) {
            child[0] = child[1] = nullptr;
        }
    };

    Node *root = nullptr;

    // helpers
    ll cnt(Node *node) { return node ? node->size : 0; }
    ll sum(Node *node) { return node ? node->sum : 0; }

    // recompute node from children
    void pull(Node *node) {
        if (!node) return;
        node->size = cnt(node->child[0]) + cnt(node->child[1]) + 1;
        node->sum = sum(node->child[0]) + sum(node->child[1]) + node->val;
    }

    // lazy propagation
    void push(Node *node) {
        if (node && node->rev) {
            node->rev = false;
            swap(node->child[0], node->child[1]);
            if (node->child[0]) node->child[0]->rev ^= true;
            if (node->child[1]) node->child[1]->rev ^= true;
        }
    }

    // merge l and r into node (all of l before all of r)
    void merge(Node *&node, Node *l, Node *r) {
        push(l), push(r);
        if (!l || !r) node = l ? l : r;
        else if (l->priority > r->priority) merge(l->child[1], l->child[1], r), node = l;
        else merge(r->child[0], l, r->child[0]), node = r;
        pull(node);
    }

    // split node into l (first key elements) and r (the rest)
    void split(Node *node, Node *&l, Node *&r, ll key) {
        if (!node) return void(l = r = nullptr);
        push(node);
        if (key <= cnt(node->child[0])) split(node->child[0], l, node->child[0], key), r = node;
        else split(node->child[1], node->child[1], r, key - cnt(node->child[0]) - 1), l = node;
        pull(node);
    }

    // operations
    ll size() { return cnt(root); }

    void insert(ll pos, ll val) {
        Node *l, *r;
        split(root, l, r, pos);
        merge(l, l, new Node(val));
        merge(root, l, r);
    }

    void erase(ll pos) {
        Node *l, *mid, *r;
        split(root, l, mid, pos);
        split(mid, mid, r, 1);
        merge(root, l, r);
    }

    void reverse(ll l, ll r) {
        Node *t1, *t2, *t3;
        split(root, t1, t2, l);
        split(t2, t2, t3, r - l + 1);
        t2->rev ^= true;
        merge(root, t1, t2);
        merge(root, root, t3);
    }

    ll qry(ll l, ll r) {
        Node *t1, *t2, *t3;
        split(root, t1, t2, l);
        split(t2, t2, t3, r - l + 1);
        ll rv = sum(t2);
        merge(root, t1, t2);
        merge(root, root, t3);
        return rv;
    }

    // in-order traversal
    vector<ll> vals() {
        vector<ll> out;
        auto go = [&](auto self, Node *node) -> void {
            if (!node) return;
            push(node);
            self(self, node->child[0]);
            out.pb(node->val);
            self(self, node->child[1]);
        };
        go(go, root);
        return out;
    }
};
