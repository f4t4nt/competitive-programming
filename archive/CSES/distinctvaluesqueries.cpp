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

struct BIT {
    vector<ll> tree;
    ll n;
    BIT(ll n) : n(n) {
        tree.resize(n + 1);
    }
    void update(ll idx, ll val) {
        idx++;
        while (idx <= n) {
            tree[idx] += val;
            idx += idx & (-idx);
        }
    }
    ll query(ll idx) {
        idx++;
        ll sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & (-idx);
        }
        return sum;
    }
    ll query(ll l, ll r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    FORE (x, a) {
        cin >> x;
    }
    map<ll, ll> ref;
    vector<ll> nxt(n, n);
    FORR (i, n) {
        if (ref.count(a[i])) {
            nxt[i] = ref[a[i]];
        }
        ref[a[i]] = i;
    }
    vector<tuple<ll, ll, ll>> queries(q);
    FOR (i, q) {
        ll l, r;
        cin >> l >> r;
        queries[i] = {l - 1, r - 1, i};
    }
    ssort(queries);
    ll l = 0;
    BIT bit(n + 1);
    set<ll> s;
    FOR (i, n) {
        if (!s.count(a[i])) {
            bit.update(i, 1);
            s.insert(a[i]);
        }
    }
    vector<ll> rv(q);
    FORE (query, queries) {
        ll ql, qr, qi;
        tie(ql, qr, qi) = query;
        while (l < ql) {
            bit.update(nxt[l], 1);
            l++;
        }
        rv[qi] = bit.query(ql, qr);
    }
    FORE (x, rv) {
        cout << x << '\n';
    }

    return 0;
}