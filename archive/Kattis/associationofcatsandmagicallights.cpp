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
#define f first
#define s second

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

struct BIT {
    vector<bitset<100>> tree; ll n;
    BIT(ll n) : n(n) { tree.resize(n + 1); }
    void update(ll idx, bitset<100> val) {
        idx++;
        while (idx <= n)
        { tree[idx] ^= val; idx += idx & (-idx); }
    }
    bitset<100> query(ll idx) {
        idx++; bitset<100> xr = 0;
        while (idx > 0)
        { xr ^= tree[idx]; idx -= idx & (-idx); }
        return xr;
    }
    bitset<100> query(ll l, ll r) { return query(r) ^ query(l - 1); }
};

bitset<100> i_to_bs(ll x) {
    bitset<100> bs; bs[x] = 1; return bs;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, q; cin >> n >> q;
    vector<bitset<100>> raw(n);
    FOR (i, n) {
        ll x; cin >> x; x--;
        raw[i] = i_to_bs(x);
    }
    vector<vector<ll>> adj(n);
    FOR (i, n - 1) {
        ll p; cin >> p; p--;
        adj[p].pb(i + 1);
    }
    ll timer = 0;
    vector<ll> in(n), out(n);
    auto dfs = [&](auto &&self, ll u, ll p) -> void {
        in[u] = timer++;
        FORE (v, adj[u]) self(self, v, u);
        out[u] = timer - 1;
    };
    dfs(dfs, 0, -1);
    BIT bit(timer + 1);
    FOR (i, n) bit.update(in[i], raw[i]);
    while (q--) {
        ll t, x; cin >> t >> x; x--;
        if (t == 0) {
            cout << bit.query(in[x], out[x]).count() << '\n';
        } else {
            auto nw = i_to_bs(t - 1);
            bit.update(in[x], nw ^ raw[x]);
            raw[x] = nw;
        }
    }

    return 0;
}