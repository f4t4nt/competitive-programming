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
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ll c, q;
        cin >> c;
        if (c == 0) break;
        vector<vector<tuple<ll, ll, ll>>> polygons(c);
        map<set<tuple<ll, ll, ll>>, vector<ll>> edges;
        vector<vector<ll>> adj(c);
        FOR (i, c) {
            ll n;
            cin >> n;
            polygons[i].resize(n);
            FORE (pt, polygons[i]) {
                ll x, y, z;
                cin >> x >> y >> z;
                pt = {x, y, z};
            }
            FOR (j, n) {
                edges[{polygons[i][j], polygons[i][(j + 1) % n]}].pb(i);
            }
        }
        FORE (e, edges) {
            assert(sz(e.second) <= 2);
            if (sz(e.second) == 2) {
                adj[e.second[0]].pb(e.second[1]);
                adj[e.second[1]].pb(e.second[0]);
            }
        }
        cin >> q;
        auto bfs = [&](ll s) {
            vector<ll> dist(c, -1);
            queue<ll> q;
            q.push(s);
            dist[s] = 0;
            while (!q.empty()) {
                ll u = q.front();
                q.pop();
                FORE (v, adj[u]) {
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.push(v);
                    }
                }
            }
            return dist;
        };
        while (q--) {
            ll a, b;
            cin >> a >> b;
            a--, b--;
            vector<ll> dist = bfs(a);
            cout << dist[b] << '\n';
        }
    }

    return 0;
}