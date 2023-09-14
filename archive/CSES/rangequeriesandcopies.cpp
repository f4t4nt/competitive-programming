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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

struct Vertex { // persistent segtree, sum
    Vertex *l, *r;
    ll sum;
    Vertex(ll val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

Vertex* build(vector<ll> &a, ll tl, ll tr) { // [tl, tr]
    if (tl == tr) return new Vertex(a[tl]);
    ll tm = (tl + tr) / 2;
    return new Vertex(build(a, tl, tm), build(a, tm + 1, tr));
}

ll get_sum(Vertex* v, ll tl, ll tr, ll l, ll r) { // [tl, tr] = [0, n - 1], [l, r]
    if (l > r) return 0;
    if (l == tl && tr == r) return v->sum;
    ll tm = (tl + tr) / 2;
    return get_sum(v->l, tl, tm, l, min(r, tm))
         + get_sum(v->r, tm + 1, tr, max(l, tm + 1), r);
}

Vertex* update(Vertex* v, ll tl, ll tr, ll pos, ll new_val) { // [tl, tr] = [0, n - 1]
    if (tl == tr) return new Vertex(new_val);
    ll tm = (tl + tr) / 2;
    if (pos <= tm) return new Vertex(update(v->l, tl, tm, pos, new_val), v->r);
    else return new Vertex(v->l, update(v->r, tm + 1, tr, pos, new_val));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, q;
    cin >> n >> q;
    vector<ll> a(n), ref = {0};
    FOR (i, n) {
        cin >> a[i];
    }
    vector<Vertex*> roots = {build(a, 0, n - 1)};
    while (q--) {
        ll t, k;
        cin >> t >> k;
        k--;
        if (t == 1) { // set
            ll a, x;
            cin >> a >> x;
            a--;
            roots[ref[k]] = update(roots[ref[k]], 0, n - 1, a, x);
        } elif (t == 2) { // query
            ll a, b, rv;
            cin >> a >> b;
            a--, b--;
            rv = get_sum(roots[ref[k]], 0, n - 1, a, b);
            cout << rv << '\n';
        } else { // copy
            ref.pb(sz(roots));
            roots.pb(new Vertex(roots[ref[k]]->l, roots[ref[k]]->r));
        }
    }

    return 0;
}