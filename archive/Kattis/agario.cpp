#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
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

struct DSU {
    ll cnt;
    vector<ll> e;
    DSU(ll n) { e = vector<ll>(n, -1); cnt = n; }
    void reset() { e = vector<ll>(sz(e), -1); cnt = sz(e); }
    ll get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool same_set(ll a, ll b) { return get(a) == get(b); }
    ll size(ll x) { return -e[get(x)]; }
    bool unite(ll x, ll y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y]; e[y] = x;
        cnt--;
        return true;
    }
};

ll dfs0(ll u, vector<vector<ll>> &children, vector<ll> &subtree_sum, vector<ll> &a) {
    ll sum = a[u];
    FORE (v, children[u]) {
        sum += dfs0(v, children, subtree_sum, a);
    }
    subtree_sum[u] = sum;
    return sum;
}

void dfs1(ll u, ll p, vector<vector<ll>> &children, vector<ll> &subtree_sum, vector<ll> &a, vector<ll> &rv) {
    rv[u] = subtree_sum[u];
    if (p != -1 && rv[u] >= a[p]) {
        rv[u] = rv[p];
    }
    FORE (v, children[u]) {
        dfs1(v, u, children, subtree_sum, a, rv);
    }
}

ll get_head(ll u, vector<ll> &head) {
    if (u == head[u]) return u;
    return head[u] = get_head(head[u], head);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    FORE (x, a) cin >> x;
    vector<tuple<ll, ll, ll>> edges0;
    FOR (i, m) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        edges0.pb({max(a[u], a[v]), u, v});
    }
    ssort(edges0);
    vector<ll> head(n);
    iota(all(head), 0);
    ll root = 0;
    vector<vector<ll>> children(n);
    DSU dsu(n);
    FORE (edge, edges0) {
        ll w, u, v;
        tie(w, u, v) = edge;
        u = get_head(u, head);
        v = get_head(v, head);
        if (a[u] < a[v]) swap(u, v);
        if (dsu.unite(u, v)) {
            children[u].pb(v);
            head[v] = u;
        } else {
            assert(u == v);
        }
    }
    FOR (i, n) {
        if (head[i] == i) {
            root = i;
            break;
        }
    }
    vector<ll> subtree_sum(n);
    dfs0(root, children, subtree_sum, a);
    vector<ll> rv(n);
    dfs1(root, -1, children, subtree_sum, a, rv);
    FORE (x, rv) cout << x << ' ';

    return 0;
}