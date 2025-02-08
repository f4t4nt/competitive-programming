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
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

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

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m1, m2; cin >> n >> m1 >> m2;
        vector<pll> edges(m1);
        FOR (i, m1) cin >> edges[i].x >> edges[i].y;
        vector<vector<ll>> adj(n + 1);
        FOR (i, m2) {
            ll u, v; cin >> u >> v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        if (n == 1) {
            cout << 0 << '\n';
            continue;
        }
        vector<ll> comp1(n + 1, -1);
        ll cnt = 0;
        FOR1 (i, n + 1) {
            if (comp1[i] == -1) {
                queue<ll> q;
                q.push(i);
                comp1[i] = cnt;
                while (!q.empty()) {
                    ll u = q.front(); q.pop();
                    for (ll v : adj[u]) {
                        if (comp1[v] == -1) {
                            comp1[v] = cnt;
                            q.push(v);
                        }
                    }
                }
                cnt++;
            }
        }
        DSU dsu(n + 1);
        ll cost_remove = 0;
        for (auto [u, v] : edges) {
            if (comp1[u] != comp1[v]) {
                cost_remove++;
            } else {
                dsu.unite(u, v);
            }
        }
        ll cost_add = 0;
        vector<vector<ll>> comp2(cnt);
        FOR1 (i, n + 1) {
            ll c = comp1[i];
            ll r = dsu.get(i);
            comp2[c].pb(r);
        }
        FOR (i, cnt) {
            auto &arr = comp2[i];
            if (arr.empty()) continue;
            ssort(arr);
            arr.erase(unique(all(arr)), arr.end());
            ll distinct_roots = sz(arr);
            cost_add += distinct_roots - 1;
        }
        cout << cost_remove + cost_add << '\n';
    }

    return 0;
}