#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long long ld;
typedef complex<ld> cd;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define ssort(C) ssort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

int main() {
    ll n, m, rv; cin >> n >> m; rv = n;
    vector<set<pll>> edges(2);
    vector<vector<set<ll>>> adj(2, vector<set<ll>>(n));
    FOR (i, m) {
        ll u, v, c; cin >> u >> v >> c;
        u--, v--;
        edges[c].insert({u, v});
        adj[c][u].insert(v);
        adj[c][v].insert(u);
    }
    for (auto [u, v] : edges[0]) {
        rv += edges[1].count({v, u}) || edges[1].count({u, v});
        bool idk = false;
        for (ll a : adj[0][u]) {
            if (a == v) continue;
            rv += 
                ((edges[1].count({u, v}) || edges[1].count({v, u})) &&
                (edges[1].count({v, a}) || edges[1].count({a, v})));
            for (ll b : adj[0][v]) {
                if (b == a) continue;
                if (b == u) continue;
                idk = true;
                rv +=
                    ((edges[1].count({u, b}) || edges[1].count({b, u})) &&
                    (edges[1].count({b, a}) || edges[1].count({a, b})) &&
                    (edges[1].count({a, v}) || edges[1].count({v, a}))) ||
                    ((edges[1].count({u, a}) || edges[1].count({a, u})) &&
                    (edges[1].count({b, a}) || edges[1].count({a, b})) &&
                    (edges[1].count({b, v}) || edges[1].count({v, b})));
            }
        }
        for (ll b : adj[0][v]) {
            if (b == u) continue;
            rv += 
                ((edges[1].count({u, v}) || edges[1].count({v, u})) &&
                (edges[1].count({u, b}) || edges[1].count({b, u})));
        }
    }
    cout << rv << '\n';
    return 0;
}