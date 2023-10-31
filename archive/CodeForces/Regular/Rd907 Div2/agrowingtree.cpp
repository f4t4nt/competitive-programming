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

struct SegTree {
    ll n;
    vector<ll> data, lazy;
    SegTree (ll n) : n(n), data(4 * n), lazy(4 * n) {}
    void push(ll i, ll l, ll r) {
        if (lazy[i] == 0) return;
        data[i] += (r - l) * lazy[i];
        if (r - l > 1) {
            lazy[2 * i] += lazy[i];
            lazy[2 * i + 1] += lazy[i];
        }
        lazy[i] = 0;
    }
    void update(ll ul, ll ur, ll val, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n;
        push(i, l, r);
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            lazy[i] += val;
            push(i, l, r);
            return;
        }
        ll m = (l + r) / 2;
        update(ul, ur, val, 2 * i, l, m);
        update(ul, ur, val, 2 * i + 1, m, r);
        data[i] = data[2 * i] + data[2 * i + 1];
    }
    void zero(ll ul, ll ur, ll i = 1, ll l = 0, ll r = -1) { // [ul, ur)
        if (r == -1) r = n;
        push(i, l, r);
        if (ur <= l || r <= ul) return;
        if (ul <= l && r <= ur) {
            data[i] = 0;
            if (r - l > 1) {
                lazy[2 * i] = 0;
                lazy[2 * i + 1] = 0;
            }
            return;
        }
        ll m = (l + r) / 2;
        zero(ul, ur, 2 * i, l, m);
        zero(ul, ur, 2 * i + 1, m, r);
        data[i] = data[2 * i] + data[2 * i + 1];
    }
    ll query(ll ql, ll qr, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        push(i, l, r);
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return data[i];
        ll m = (l + r) / 2;
        return query(ql, qr, 2 * i, l, m) + query(ql, qr, 2 * i + 1, m, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll q, n = 1;
        cin >> q;
        vector<vector<ll>> adj(1);
        vector<vector<ll>> queries;
        while (q--) {
            ll t, v, x;
            cin >> t >> v;
            v--;
            if (t == 1) {
                adj[v].pb(n++);
                adj.pb({});
                queries.pb({t, v});
            } else {
                cin >> x;
                queries.pb({t, v, x});
            }
        }
        ll cnt = 0;
        vector<ll> lo(n), hi(n);
        auto dfs = [&](auto &f, ll v) -> void {
            lo[v] = cnt++;
            FORE (u, adj[v]) {
                f(f, u);
            }
            hi[v] = cnt;
        };
        dfs(dfs, 0);
        SegTree st(n);
        n = 1;
        FORE (q, queries) {
            if (q[0] == 1) {
                st.zero(lo[n], hi[n]);
                n++;
            } else {
                ll v = q[1], x = q[2];
                st.update(lo[v], hi[v], x);
            }
        }
        ll tmp = st.query(0, n);
        vector<ll> rv(n);
        FOR (i, n) {
            rv[i] = st.query(lo[i], lo[i] + 1);
        }
        FORE (x, rv) {
            cout << x << ' ';
        }
        cout << '\n';
    }

    return 0;
}