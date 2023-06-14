#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
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

vector<vector<ll>> scc(vector<vector<ll>> adj) {
    ll n = sz(adj);
    vector<ll> order;
    vector<bool> vis(n);
    function<void(ll)> dfs = [&](ll u) {
        vis[u] = true;
        FORE(v, adj[u]) {
            if (!vis[v]) {
                dfs(v);
            }
        }
        order.pb(u);
    };
    FOR(i, n) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    vector<vector<ll>> adjt(n);
    FOR(i, n) {
        FORE(j, adj[i]) {
            adjt[j].pb(i);
        }
    }
    vector<vector<ll>> sccs;
    vis.assign(n, false);
    function<void(ll, vector<ll> &)> dfs2 = [&](ll u, vector<ll> &scc) {
        vis[u] = true;
        scc.pb(u);
        FORE(v, adjt[u]) {
            if (!vis[v]) {
                dfs2(v, scc);
            }
        }
    };
    FORR(i, n) {
        if (!vis[order[i]]) {
            vector<ll> scc;
            dfs2(order[i], scc);
            sccs.pb(scc);
        }
    }
    return sccs;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n);
    FOR (i, m) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
    }

    vector<vector<ll>> sccs = scc(adj);
    vector<ll> cats(n);
    FOR (i, sz(sccs)) {
        FORE (u, sccs[i]) {
            cats[u] = i + 1;
        }
    }

    cout << sz(sccs) << '\n';
    FORE (cat, cats) {
        cout << cat << ' ';
    }
    cout << '\n';

    return 0;
}