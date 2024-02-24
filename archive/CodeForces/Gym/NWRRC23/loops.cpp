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
    pld,
    null_type,
    less<pld>,
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
    ll idx;
    Node *l, *r;
    Node(ll idx) : idx(idx), l(0), r(0) {}
    bool operator<(const Node &node) const {
        Node *lo = l, *hi = r;
        while (lo && hi) {
            if (lo->idx == node.idx) return false;
            if (hi->idx == node.idx) return true;
            lo = lo->r, hi = hi->r;
        }
        return hi;
    }
    void push_left(Node *node) {
        if (l) l->r = node;
        node->l = l;
        l = node;
        node->r = this;
    }
    void push_right(Node *node) {
        if (r) r->l = node;
        node->r = r;
        r = node;
        node->l = this;
    }
    void print() {
        cout << idx << ' ';
        if (r) r->print();
    }
    void scan(ll a, ll b, ll c, bool &abc, bool &bac, bool &bca, bool &cab, bool &cba, bool &acb) {
        auto it = this;
        while (it->idx != a && it->idx != b && it->idx != c) it = it->r;
        if (it->idx == a) {
            while (it->idx != b && it->idx != c) it = it->r;
            if (it->idx == b) abc = true;
            elif (it->idx == c) acb = true;
        } elif (it->idx == b) {
            while (it->idx != a && it->idx != c) it = it->r;
            if (it->idx == a) bac = true;
            elif (it->idx == c) bca = true;
        } elif (it->idx == c) {
            while (it->idx != a && it->idx != b) it = it->r;
            if (it->idx == a) cab = true;
            elif (it->idx == b) cba = true;
        }
    }
    void bscan(ll a, ll c, bool &abc, bool &bac, bool &bca, bool &cab, bool &cba, bool &acb) {
        auto lo = this, hi = this;
        while (lo && hi && lo->idx != a && lo->idx != c && hi->idx != a && hi->idx != c) {
            lo = lo->l, hi = hi->r;
        }
        if (!lo) {
            while (hi->idx != a && hi->idx != c) hi = hi->r;
            if (hi->idx == a) bac = true;
            elif (hi->idx == c) bca = true;
        } elif (!hi) {
            while (lo->idx != a && lo->idx != c) lo = lo->l;
            if (lo->idx == a) cab = true;
            elif (lo->idx == c) acb = true;
        } elif (lo->idx == a) {
            while (lo && hi && lo->idx != c && hi->idx != c) {
                lo = lo->l, hi = hi->r;
            }
            if (!lo) abc = true;
            elif (!hi) cab = true;
            elif (lo->idx == c) cab = true;
            elif (hi->idx == c) abc = true;
        } elif (lo->idx == c) {
            while (lo && hi && lo->idx != a && hi->idx != a) {
                lo = lo->l, hi = hi->r;
            }
            if (!lo) cba = true;
            elif (!hi) acb = true;
            elif (lo->idx == a) acb = true;
            elif (hi->idx == a) cba = true;
        } elif (hi->idx == a) {
            while (lo && hi && lo->idx != c && hi->idx != c) {
                lo = lo->l, hi = hi->r;
            }
            if (!lo) bac = true;
            elif (!hi) cba = true;
            elif (lo->idx == c) cba = true;
            elif (hi->idx == c) bac = true;
        } elif (hi->idx == c) {
            while (lo && hi && lo->idx != a && hi->idx != a) {
                lo = lo->l, hi = hi->r;
            }
            if (!lo) bca = true;
            elif (!hi) abc = true;
            elif (lo->idx == a) abc = true;
            elif (hi->idx == a) bca = true;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m; cin >> n >> m;
    vector<str> loops(n - 1);
    vector<vector<Node*>> ref(n, vector<Node*>(m));
    vector<vector<ld>> ans(n, vector<ld>(m));
    FOR(i, n - 1) cin >> loops[i];
    Node *root = new Node(-1);
    FOR (i, n) FOR (j, m) ref[i][j] = new Node(j * n + i);
    FOR (i, n) root->push_right(ref[i][0]);
    FOB (j, 1, m) root->push_right(ref[0][j]);
    // root->print(); cout << endl;
    FOR (i, n - 1) FOR (j, m - 1) {
        auto a = ref[i][j], b = ref[i + 1][j], c = ref[i][j + 1], d = ref[i + 1][j + 1];
        // bool ab = *a < *b, bc = *b < *c, ac = *a < *c, ba = !ab, cb = !bc, ca = !ac;
        ll ai = a->idx, bi = b->idx, ci = c->idx;
        bool abc = false, bac = false, bca = false, cab = false, cba = false, acb = false;
        // root->scan(ai, bi, ci, abc, bac, bca, cab, cba, acb);      
        b->bscan(ai, ci, abc, bac, bca, cab, cba, acb);  
        if (loops[i][j] == '1') {
            if (abc) b->push_left(d);
            elif (acb) b->push_right(d);
            elif (bac) a->push_left(d);
            elif (cab) b->push_left(d);
            elif (bca) a->push_right(d);
            elif (cba) a->push_left(d);
            else assert(false);
        } elif (loops[i][j] == '2') {
            if (abc) c->push_left(d);
            elif (acb) b->push_left(d);
            elif (bac) c->push_right(d);
            elif (cab) b->push_right(d);
            elif (bca) c->push_left(d);
            elif (cba) b->push_left(d);
            else assert(false);
        } elif (loops[i][j] == '3') {
            if (abc) c->push_right(d);
            elif (acb) c->push_left(d);
            elif (bac) c->push_left(d);
            elif (cab) a->push_left(d);
            elif (bca) a->push_left(d);
            elif (cba) a->push_right(d);
            else assert(false);
        }
        // root->print(); cout << endl;
    }
    ll cnt = 1;
    auto it = root->r;
    while (it) {
        ll i = it->idx % n, j = it->idx / n;
        ans[i][j] = cnt++;
        it = it->r;
    }
    FOR (i, n) {
        FOR (j, m) cout << (ll) ans[i][j] << ' ';
        cout << '\n';
    }

    return 0;
}