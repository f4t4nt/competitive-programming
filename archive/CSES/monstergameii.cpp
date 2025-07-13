#include <bits/stdc++.h>
using namespace std;

typedef __int128 i128;
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

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
// s.order_of_key(x) -> number of elements < x
// s.find_by_order(x) -> iterator to the x-th element (0-indexed)

#pragma GCC target("popcnt,lzcnt")
// __builtin_popcount(x) -> number of set bits
// __builtin_clz(x) -> number of leading zeros
// for ll, use __builtin_popcountll, __builtin_clzll

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define f first
// #define s second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll INF = 4e18;

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, x0; cin >> n >> x0;
    vector<ll> s(n), f(n), dp(n);
    for (ll &x : s) cin >> x;
    for (ll &x : f) cin >> x;
    LiChao hull(0, 1e6);
    hull.add_line({x0, 0});
    for (ll i = 0; i < n; i++) {
        dp[i] = hull.query(s[i]);
        hull.add_line({f[i], dp[i]});
    }
    cout << dp[n - 1] << '\n';

    return 0;
}
