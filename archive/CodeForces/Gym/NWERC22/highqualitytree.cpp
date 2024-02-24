#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define x first
#define y second
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

ll ans = 0;

void dfs(ll cur, vector<vector<ll>> &adj, vector<ll> &par) {
    for (ll to : adj[cur]) {
        if (par[to] == -1) {
            par[to] = cur;
            dfs(to, adj, par);
        }
    }
}

vector<ll> dfs2(ll cur, vector<vector<ll>> &adj, vector<ll> &par) {
    vector<vector<ll>> children;
    for (ll to : adj[cur]) {
        if (to != par[cur]) {
            children.pb(dfs2(to, adj, par));
        }
    }

    while (sz(children) != 2) children.pb({});

    ll max_len = min(sz(children[0]), sz(children[1])) + 1;
    vector<ll> cur_subtree(max_len + 1, 0);

    cur_subtree[0] = 1;
    FOR(i, max_len) {
        FOR(j, 2) {
            if (i < sz(children[j])) {
                cur_subtree[i + 1] += children[j][i];
            }
        }
    }
    FOR(i, 2) {
        for (ll j = max_len; j < sz(children[i]); j++) {
            ans += children[i][j];
        }
    }
    if (cur_subtree[sz(cur_subtree) - 1] == 0) cur_subtree.pop_back();
    return cur_subtree;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;

    vector<vector<ll>> adj(n);
    vector<ll> par(n, -1);
    FOR(i, n - 1) {
        ll u, v; cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    par[0] = 0;
    dfs(0, adj, par);
    dfs2(0, adj, par);
    cout << ans << "\n";

    return 0;
}