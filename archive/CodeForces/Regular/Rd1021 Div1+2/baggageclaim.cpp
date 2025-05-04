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

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
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

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

const ll MOD = 1e9 + 7;

struct DSU {
    ll cnt; vector<ll> e;
    DSU(ll n) : cnt(n), e(n, -1) {}
    void reset() { e = vector<ll>(sz(e), -1); cnt = sz(e); }
    ll get(ll x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m, k; cin >> n >> m >> k;
        map<pll, ll> ids;
        vector<vector<ll>> adj;
        auto get_id = [&](pll p) -> ll {
            auto it = ids.find(p);
            if (it == ids.end()) {
                ll new_id = sz(ids);
                adj.pb({});
                return ids[p] = new_id;
            }
            return it->s;
        };
        vector<pll> pos(k + 1);
        cin >> pos[0].f >> pos[0].s;
        bool ok = true;
        for (ll i = 1; i <= k; i++) {
            cin >> pos[i].f >> pos[i].s;
            ll dx = pos[i].f - pos[i - 1].f,
                dy = pos[i].s - pos[i - 1].s;
            if (abs(dx) + abs(dy) != 2) {
                ok = false;
            } elif (abs(dx) == 2 || abs(dy) == 2) {
                ll x = (pos[i].f + pos[i - 1].f) / 2,
                    y = (pos[i].s + pos[i - 1].s) / 2,
                    u = get_id({x, y});
                adj[u].pb(u);
            } else {
                ll x1 = pos[i].f,
                    x2 = pos[i - 1].f,
                    y1 = pos[i].s,
                    y2 = pos[i - 1].s,
                    u = get_id({x1, y2}),
                    v = get_id({x2, y1});
                adj[u].pb(v);
            }
        }
        if (!ok) {
            cout << 0 << '\n';
            continue;
        }
        DSU dsu(sz(adj));
        vector<bool> loop(sz(adj));
        for (ll u = 0; u < sz(adj); u++) {
            for (ll v : adj[u]) {
                dsu.unite(u, v);
                if (u == v) loop[u] = true;
            }
        }
        vector<ll> cnts(sz(adj));
        for (ll u = 0; u < sz(adj); u++) {
            cnts[dsu.get(u)] += sz(adj[u]);
            loop[dsu.get(u)] = loop[dsu.get(u)] || loop[u];
        }
        ll ans = 1;
        for (ll u = 0; u < sz(adj); u++) {
            if (u != dsu.get(u)) continue;
            ll ecnt = cnts[u], vcnt = dsu.size(u);
            if (ecnt > vcnt) {
                ans = 0;
                break;
            } elif (ecnt == vcnt && !loop[u]) {
                ans = (ans * 2) % MOD;
            } elif (ecnt == vcnt - 1) {
                ans = (ans * vcnt) % MOD;
            }
        }
        cout << ans << '\n';
    }

    return 0;
}