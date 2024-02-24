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

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
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
#define x first
#define y second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

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
    ll label, priority, size = 1, sum;
    Node *child[2];
    Node(ll label) : label(label), priority(rng()), sum(label) {
        child[0] = child[1] = nullptr;
    }
};

struct Treap {
    Node *ROOT = nullptr;

    ll cnt(Node *node) { return node ? node->size : 0; }

    void upd_cnt(Node *node)
    { if (node) node->size = cnt(node->child[0]) + cnt(node->child[1]) + 1; }

    ll sum(Node *node) { return node ? node->sum : 0; }

    void upd_sum(Node *node)
    { if (node) node->sum = sum(node->child[0]) + sum(node->child[1]) + node->label; }

    void merge(Node *&node, Node *l, Node *r) { // merges l and r into node
        if (!l || !r) node = l ? l : r;
        elif (l->priority > r->priority) merge(l->child[1], l->child[1], r), node = l;
        else merge(r->child[0], l, r->child[0]), node = r;
        upd_cnt(node);
        upd_sum(node);
    }

    void split(Node *node, Node *&l, Node *&r, ll key, ll add = 0) { // splits node into l and r
        if (!node) return void(l = r = nullptr);
        ll cur_key = add + cnt(node->child[0]);
        if (key <= cur_key) split(node->child[0], l, node->child[0], key, add), r = node;
        else split(node->child[1], node->child[1], r, key, add + 1 + cnt(node->child[0])), l = node;
        upd_cnt(node);
        upd_sum(node);
    }

    void output(Node *node) { // inorder traversal
        if (!node) return;
        output(node->child[0]);
        cout << node->label << ' ';
        output(node->child[1]);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    Treap treap;
    FOR (i, n) treap.merge(treap.ROOT, treap.ROOT, new Node(i + 1));
    FOR (i, n) {
        // treap.output(treap.ROOT); cout << '\n';
        ll a, b; cin >> a >> b;
        if (a >= b) continue;
        a--, b--;
        ll len = min(b - a, n - b);
        Node *t1, *t2, *t3, *t4, *t5;
        // t1: [0, a - 1], t2: [a, a + len - 1], t3: [a + len, b - 1], t4: [b, b + len - 1], t5: [b + len, n - 1]
        treap.split(treap.ROOT, t1, t2, a);
        treap.split(t2, t2, t3, len);
        treap.split(t3, t3, t4, b - a - len);
        treap.split(t4, t4, t5, len);
        // treap.output(t1); cout << " | "; treap.output(t2); cout << " | "; treap.output(t3); cout << " | "; treap.output(t4); cout << " | "; treap.output(t5); cout << '\n';
        treap.merge(treap.ROOT, t1, t4);
        treap.merge(treap.ROOT, treap.ROOT, t3);
        treap.merge(treap.ROOT, treap.ROOT, t2);
        treap.merge(treap.ROOT, treap.ROOT, t5);
    }
    treap.output(treap.ROOT); cout << '\n';

    return 0;
}