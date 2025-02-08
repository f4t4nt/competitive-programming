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
// #define x first
// #define y second

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

const ll KMAX = 300;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<set<ll>> adj(n);
        vector<ll> deg(n);
        FOR (i, n - 1) {
            ll u, v; cin >> u >> v;
            u--, v--;
            adj[u].insert(v);
            adj[v].insert(u);
            deg[u]++;
            deg[v]++;
        }
        if (n == 2) {
            cout << 0 << '\n';
            continue;
        }
        vector<pll> dv(n);
        FOR (i, n) dv[i] = {deg[i], i};
        rsort(dv);
        ll ans = 0, k = min(n, KMAX);
        FOR (i, k) {
            auto [dx, x] = dv[i];
            if (dx == 0) continue;
            ll dz = -1;
            for (ll z : adj[x]) {
                dz = max(dz, deg[z]);
            }
            if (dz >= 0) {
                ans = max(ans, dx + dz - 2);
            }
            for (auto [dy, y] : dv) {
                if (y == x || adj[x].count(y)) continue;
                ans = max(ans, dx + dy - 1);
                break;
            }
        }
        cout << ans << '\n';
    }

    return 0;
}