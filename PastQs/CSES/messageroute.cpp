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
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    vector<pair<ll, ll>> edges(m);
    vector<vector<ll>> adj(n);
    FOR (i, m) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        edges[i] = mp(a, b);
        adj[a].pb(b);
        adj[b].pb(a);
    }

    vector<ll> dist(n, 1e18), prev(n, -1);
    queue<ll> q;
    q.push(0);
    dist[0] = 0;
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        FORE (v, adj[u]) {
            if (dist[v] == 1e18) {
                dist[v] = dist[u] + 1;
                prev[v] = u;
                q.push(v);
            }
        }
    }

    if (dist[n - 1] == 1e18) {
        cout << "IMPOSSIBLE\n";
    } else {
        vector<ll> path;
        ll u = n - 1;
        while (u != -1) {
            path.pb(u);
            u = prev[u];
        }
        flip(path);
        cout << sz(path) << '\n';
        FORE (v, path) cout << v + 1 << ' ';
        cout << '\n';
    }

    return 0;
}