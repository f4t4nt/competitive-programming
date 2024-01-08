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

const ll MOD = 1e6 + 3;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, s;
    cin >> n >> m >> s;
    // adj[v] incoming trains to v
    // <from, t0, duration, period>
    vector<vector<tuple<ll, ll, ll, ll>>> adj(n);
    FOR (i, m) {
        ll u, v, t0, p, d;
        cin >> u >> v >> t0 >> p >> d;
        adj[v].pb({u, t0, d, p});
    }
    // latest time to reach i
    vector<ll> latest(n, -1e18);
    latest[n - 1] = s;
    // <time, node>, largest time first
    std::priority_queue<pair<ll, ll>> pq;
    pq.push({s, n - 1});
    while (!pq.empty()) {
        auto [t, v] = pq.top();
        pq.pop();
        if (t < latest[v]) {
            continue;
        }
        FORE (e, adj[v]) {
            auto [u, t0, d, p] = e;
            // find closest t_in = t0 + k * p + d <= t
            ll k = (t - t0 - d) / p;
            if (k < 0) {
                continue;
            }
            ll t_in = t0 + k * p + d,
               t_out = t_in - d;
            if (t_out > latest[u]) {
                latest[u] = t_out;
                pq.push({t_out, u});
            }
        }
    }
    if (latest[0] >= 0) {
        cout << latest[0] << '\n';
    } else {
        cout << "impossible\n";
    }

    return 0;
}