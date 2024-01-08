#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // # of cities, # of roads, min time between revisits, max time of travel, start city
    ll n, r, h, max_t, s;
    cin >> n >> r >> h >> max_t >> s;
    // <time to drive, city id>
    vector<set<pair<ll, ll>>> adj(n);
    // time to visit city
    vector<ll> vis_t(n), last_t(n, LLONG_MIN);
    map<str, ll> city_id;
    vector<str> city_name(n);
    FOR (i, n) {
        ll j;
        cin >> j >> city_name[j] >> vis_t[j];
        city_id[city_name[j]] = j;
    }
    FOR (i, r) {
        ll u, v, t;
        cin >> u >> v >> t;
        adj[u].insert({t, v});
        adj[v].insert({t, u});
    }
    pair<ll, ll> cur = {vis_t[s], s}, nxt = {LLONG_MAX, -1};
    vector<str> rv;
    while (true) {
        ll t = cur.first;
        ll u = cur.second;
        rv.pb(city_name[u]);
        last_t[u] = t;
        for (auto [dt, v] : adj[u]) {
            if (last_t[v] + h <= t + dt && t + dt + vis_t[v] <= max_t) {
                nxt = min(nxt, {t + dt, v});
            }
        }
        if (nxt.first == LLONG_MAX) break;
        cur = nxt;
        cur.first += vis_t[cur.second];
        nxt = {LLONG_MAX, -1};
    }
    FORE (x, rv) cout << x << ' ';
    cout << '\n';
    cout << cur.first << '\n';

	return 0;
}
