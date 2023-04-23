#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

// https://open.kattis.com/problems/bogofeternalstench

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<tuple<ll, ll, ll>> edges;
    FOR (i, m) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        edges.pb({c, a, b});
    }
    vector<vector<pair<ll, ll>>> adj(n);
    FORE (e, edges) {
        ll c, a, b;
        tie(c, a, b) = e;
        adj[a].pb({b, c});
        adj[b].pb({a, c});
    }

    vector<ll> dist(n, 1e18);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
    pq.push({0, 0});
    dist[0] = 0;
    while (!pq.empty()) {
        ll d, u;
        tie(d, u) = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        FORE (e, adj[u]) {
            ll v, w;
            tie(v, w) = e;
            ll nd = max(dist[u] + w, 0LL);
            if (dist[v] > nd) {
                dist[v] = nd;
                pq.push({dist[v], v});
            }
        }
    }
    cout << dist[n - 1] << '\n';

    return 0;
}