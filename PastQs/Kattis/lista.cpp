#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (int) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(int x = 0; x < (int) e; x++)
#define FORR(x, e) for(int x = (int) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(int x = 0; x < (int) e; x += (int) i)
#define FOBI(x, b, e, i) for(int x = (int) b; x < (int) e; x += (int) i)
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
    int val;
    Node *prev, *next;
    Node(int val) : val(val), prev(nullptr), next(nullptr) {}
};

struct List {
    Node *head, *tail;
    List() : head(nullptr), tail(nullptr) {}
    void push_back(Node *node) {
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }
    void move_before(Node *x, Node *y) {
        if (x == y) return;
        if (x->prev != nullptr) x->prev->next = x->next;
        if (x->next != nullptr) x->next->prev = x->prev;
        if (x == head) head = x->next;
        if (x == tail) tail = x->prev;
        x->prev = y->prev;
        x->next = y;
        if (y->prev != nullptr) y->prev->next = x;
        y->prev = x;
        if (y == head) head = x;
    }
    void move_after(Node *x, Node *y) {
        if (x == y) return;
        if (x->prev != nullptr) x->prev->next = x->next;
        if (x->next != nullptr) x->next->prev = x->prev;
        if (x == head) head = x->next;
        if (x == tail) tail = x->prev;
        x->prev = y;
        x->next = y->next;
        if (y->next != nullptr) y->next->prev = x;
        y->next = x;
        if (y == tail) tail = x;
    }
    vector<ll> get_vec() {
        vector<ll> rv;
        Node *cur = head;
        while (cur != nullptr) {
            rv.pb(cur->val);
            cur = cur->next;
        }
        return rv;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<Node*> nodes(n);
    FOR (i, n) {
        nodes[i] = new Node(i + 1);
    }

    List list;
    FOR (i, n) {
        list.push_back(nodes[i]);
    }

    while (m--) {
        ch t;
        ll x, y;
        cin >> t >> x >> y;
        x--, y--;
        if (t == 'A') {
            list.move_before(nodes[x], nodes[y]);
        } elif (t == 'B') {
            list.move_after(nodes[x], nodes[y]);
        }
    }

    vector<ll> vec = list.get_vec(), lis, prev(n, -1);
    FOR (i, n) {
        ll pos = lower_bound(all(lis), vec[i]) - lis.begin();
        if (pos == sz(lis)) {
            prev[vec[i] - 1] = lis.empty() ? -1 : lis.back();
            lis.pb(vec[i]);
        } else {
            prev[vec[i] - 1] = pos == 0 ? -1 : lis[pos - 1];
            lis[pos] = vec[i];
        }
    }

    ll cur = lis.back();
    lis.clear();
    while (cur != -1) {
        lis.pb(cur);
        cur = prev[cur - 1];
    }

    set<ll> lis_s;
    FORE (x, lis) {
        lis_s.insert(x);
    }

    vector<pair<ll, ll>> rv;
    FOR (i, n) {
        if (lis_s.count(i + 1)) {
            continue;
        }
        auto it = lis_s.lower_bound(i + 1);
        ll x;
        if (it == lis_s.end()) {
            it--;
        }
        x = *it;
        lis_s.insert(i + 1);
        rv.pb({i + 1, x});
    }

    cout << sz(rv) << '\n';
    FORE (x, rv) {
        cout << (x.first < x.second ? 'A' : 'B') << ' ' << x.first << ' ' << x.second << '\n';
        // if (x.first < x.second) {
        //     list.move_before(nodes[x.first - 1], nodes[x.second - 1]);
        // } else {
        //     list.move_after(nodes[x.first - 1], nodes[x.second - 1]);
        // }
    }

    return 0;
}