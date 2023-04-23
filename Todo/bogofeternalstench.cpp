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
    vector<vector<pair<ll, ll>>> adj(n);
    FOR (i, m) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].pb({b, c});
    }

    vector<ll> dist(n, 1e18);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        ll v, d;
        tie(d, v) = pq.top();
        pq.pop();
        if (d > dist[v]) {
            continue;
        }
        FORE (edge, adj[v]) {
            ll u, c;
            tie(u, c) = edge;
            ll nd = max(d + c, 0LL);
            if (dist[u] > nd) {
                dist[u] = nd;
                pq.push({nd, u});
            }
        }
    }
    cout << dist[n - 1] << '\n';

    return 0;
}