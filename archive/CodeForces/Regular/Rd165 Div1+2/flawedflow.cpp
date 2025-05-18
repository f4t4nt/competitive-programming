#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define f first
// #define s second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

struct Edge {
    ll s, t, flow;
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m; cin >> n >> m;
    vector<ll> flow(n);
    vector<Edge> edges(2 * m);
    vector<vector<ll>> adj(n);
    for (ll i = 0; i < 2 * m; i += 2) {
        ll u, v, f; cin >> u >> v >> f;
        u--, v--;
        edges[i] = { u, v, f };
        edges[i + 1] = { v, u, f };
        adj[u].pb(i);
        adj[v].pb(i + 1);
        flow[u] += f;
        flow[v] += f;
    }
    flow[0] = 0;
    for (ll i = 1; i < n - 1; i++) flow[i] /= 2;
    vector<ll> ans(m);
    queue<ll> q;
    q.push(0);
    while (!q.empty()) {
        ll v = q.front(); q.pop();
        for (ll id : adj[v]) {
            ll u = edges[id].t;
            if (flow[u] == 0) continue;
            ans[id / 2] = id & 1;
            flow[u] -= edges[id].flow;
            if (flow[u] == 0) q.push(u);
        }
    }
    for (ll x : ans) cout << x << '\n';

    return 0;
}
