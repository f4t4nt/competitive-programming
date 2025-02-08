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

void dfs(ll u, ll p, vector<map<ll, vector<ll>>> &adj, set<pll> &blast, vector<bool> &ok, bool &del) {
    blast.erase({p, u});
    auto it = blast.find({u, p});
    if (it != blast.end()) {
        blast.erase(it);
        del = true;
    }
    ok[u] = false;
    for (auto &[k, vec] : adj[u]) {
        for (ll v : vec) {
            if (v != p) {
                dfs(v, u, adj, blast, ok, del);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    vector<map<ll, vector<ll>>> adj(n);
    FOR (_, n - 1) {
        ll u, v, c; cin >> u >> v >> c;
        u--, v--, c--;
        adj[u][c].pb(v);
        adj[v][c].pb(u);
    }
    set<pll> blast;
    FOR (u, n) {
        for (auto &[k, vec] : adj[u]) {
            if (sz(vec) > 1) {
                for (ll v : vec) {
                    blast.insert({u, v});
                }
            }
        }
    }
    vector<bool> ok(n, true);
    while (sz(blast)) {
        bool del = false;
        auto [u, v] = *blast.begin();
        dfs(v, u, adj, blast, ok, del);
        if (del) {
            dfs(u, v, adj, blast, ok, del);
        }
    }
    vector<ll> res;
    FOR (i, n) if (ok[i]) res.pb(i);
    cout << sz(res) << '\n';
    for (ll i : res) cout << i + 1 << '\n';

    return 0;
}