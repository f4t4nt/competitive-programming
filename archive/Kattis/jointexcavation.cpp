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

bool dfs(ll v, vector<ll> &path, set<ll> &a, set<ll> &b, vector<set<ll>> &adj, vector<bool> &vis) {
    a.erase(v);
    path.pb(v);
    if (sz(a) == sz(b)) {
        return true;
    }
    vis[v] = true;
    FORE (u, adj[v]) {
        if (!vis[u] && dfs(u, path, a, b, adj, vis)) {
            return true;
        }
    }
    path.pop_back();
    b.insert(v);
    ll sza = sz(a), szb = sz(b);
    return sz(a) == sz(b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll c, t;
    cin >> c >> t;
    vector<set<ll>> adj(c);
    FOR (i, t) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    vector<ll> path = {};
    set<ll> a, b;
    FOR (j, c) {
        a.insert(j);
    }
    vector<bool> vis(c);
    assert(dfs(0, path, a, b, adj, vis));
    cout << sz(path) << ' ' << sz(a) << '\n';
    FORE (v, path) {
        cout << v + 1 << ' ';
    }
    cout << '\n';
    FORE (v, a) {
        cout << v + 1 << ' ';
    }
    cout << '\n';
    FORE (v, b) {
        cout << v + 1 << ' ';
    }
    cout << '\n';

    return 0;
}