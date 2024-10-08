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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<vector<pair<ll, ll>>> adj(n + 1);
    FOR (i, n) {
        adj[i + 1].pb({i, 1});
        adj[i].pb({i + 1, 1});
    }
    FOR (i, m) {
        ll t, l, r, v;
        cin >> t >> l >> r >> v;
        l--;
        v = v / 2 * 2;
        if (t) swap(l, r);
        adj[l].pb({r, v});
    }
    vector<ll> d(n + 1, 1e18);
    d[0] = 0;
    std::priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();
        if (w > d[u]) continue;
        FORE (e, adj[u]) {
            auto [v, c] = e;
            if (d[v] > d[u] + c) {
                d[v] = d[u] + c;
                pq.push({d[v], v});
            }
        }
    }
    str rv = str(n, '0');
    FOR (i, n) if (d[i + 1] < d[i]) rv[i] = '1';
    cout << rv << '\n';

    return 0;
}