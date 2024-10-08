#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
 
#pragma GCC target("popcnt,lzcnt")
 
#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
 
#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FORE(x, C) for(auto &x : C)
 
#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

struct Node {
    ch label;
    ll priority, size = 1;
    bool rev = false;
    Node *child[2];
    Node(ch label) : label(label), priority(rng()) {
        child[0] = child[1] = nullptr;
    }
};

struct Treap {
    Node *root = nullptr;

    ll cnt(Node *node) { return node ? node->size : 0; }

    void upd_cnt(Node *node)
    { if (node) node->size = cnt(node->child[0]) + cnt(node->child[1]) + 1; }

    void push(Node *node) {
        if (node && node->rev) {
            node->rev = false;
            swap(node->child[0], node->child[1]);
            if (node->child[0]) node->child[0]->rev ^= true;
            if (node->child[1]) node->child[1]->rev ^= true;
        }
    }

    void merge(Node *&node, Node *l, Node *r) {
        push(l), push(r);
        if (!l || !r) node = l ? l : r;
        elif (l->priority > r->priority) merge(l->child[1], l->child[1], r), node = l;
        else merge(r->child[0], l, r->child[0]), node = r;
        upd_cnt(node);
    }

    void split(Node *node, Node *&l, Node *&r, ll key, ll add = 0) {
        if (!node) return void(l = r = nullptr);
        push(node);
        ll cur_key = add + cnt(node->child[0]);
        if (key <= cur_key) split(node->child[0], l, node->child[0], key, add), r = node;
        else split(node->child[1], node->child[1], r, key, add + 1 + cnt(node->child[0])), l = node;
        upd_cnt(node);
    }

    void reverse(Node *node, ll l, ll r) {
        Node *t1, *t2, *t3;
        split(node, t1, t2, l);
        split(t2, t2, t3, r - l + 1);
        t2->rev ^= true;
        merge(node, t1, t2);
        merge(node, node, t3);
    }

    void output(Node *node) {
        if (!node) return;
        push(node);
        output(node->child[0]);
        cout << node->label;
        output(node->child[1]);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll n, q;
    cin >> n >> q;
    str s;
    cin >> s;
    Treap treap;
    FORE(c, s) treap.merge(treap.root, treap.root, new Node(c));
    while (q--) {
        ll l, r;
        cin >> l >> r;
        Node *t1, *t2, *t3;
        treap.split(treap.root, t1, t2, l - 1);
        treap.split(t2, t2, t3, r - l + 1);
        treap.merge(treap.root, t1, t3);
        treap.merge(treap.root, treap.root, t2);
    }
    treap.output(treap.root);

    return 0;
}