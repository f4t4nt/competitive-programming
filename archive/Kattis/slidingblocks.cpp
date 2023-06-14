#include <bits/stdc++.h>
    
using namespace std;
    
using ll = long long;
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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

constexpr ll INF = 1e18;

void dfs(
    ll v,
    vector<vector<pair<ll, ch>>> &adj,
    vector<ll> &par,
    vector<ch> &dir,
    vector<bool> &vis
) {
    vis[v] = true;
    FORE (u, adj[v]) {
        if (!vis[u.first]) {
            par[u.first] = v;
            dir[u.first] = u.second;
            dfs(u.first, adj, par, dir, vis);
        }
    }
}

bool top_sort(vector<set<ll>> &adj, vector<ll> &order) {
    vector<ll> in(sz(adj));
    FORE (v, adj) {
        FORE (u, v) {
            in[u]++;
        }
    }
    queue<ll> q;
    FOR (i, sz(adj)) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        order.pb(v);
        FORE (u, adj[v]) {
            in[u]--;
            if (in[u] == 0) {
                q.push(u);
            }
        }
    }
    return sz(order) == sz(adj) && order[0] == 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, b;
    cin >> n >> m >> b;
    map<pair<ll, ll>, ll> ref;
    map<ll, set<pair<ll, ll>>> xs, ys;
    vector<pair<ll, ll>> inv;
    FOR (i, b) {
        ll x, y;
        cin >> y >> x;
        ref[{x, y}] = i;
        inv.pb({x, y});
        xs[x].insert({y, i});
        ys[y].insert({x, i});
    }
    vector<vector<pair<ll, ch>>> adj(b);
    FOR (i, b) {
        ll x, y;
        tie(x, y) = inv[i];
        if (ref.count({x + 1, y})) {
            adj[i].pb({ref[{x + 1, y}], '<'});
        }
        if (ref.count({x - 1, y})) {
            adj[i].pb({ref[{x - 1, y}], '>'});
        }
        if (ref.count({x, y + 1})) {
            adj[i].pb({ref[{x, y + 1}], '^'});
        }
        if (ref.count({x, y - 1})) {
            adj[i].pb({ref[{x, y - 1}], 'v'});
        }
    }
    vector<ll> par(b);
    vector<ch> dir(b);
    vector<bool> vis(b);
    dfs(0, adj, par, dir, vis);
    vector<set<ll>> adj_mod(b);
    FOR (i, b) {
        if (i == 0) {
            FOB (j, 1, b) {
                adj_mod[i].insert(j);
            }
            continue;
        }
        adj_mod[par[i]].insert(i);
        ll x, y;
        tie(x, y) = inv[i];
        if (dir[i] == '>') {
            auto it = ys[y].lower_bound({x, -1});
            if (it != ys[y].begin()) {
                it--;
                adj_mod[i].insert(it->second);
            }
        } elif (dir[i] == '<') {
            auto it = ys[y].upper_bound({x, INF});
            if (it != ys[y].end()) {
                adj_mod[i].insert(it->second);
            }
        } elif (dir[i] == 'v') {
            auto it = xs[x].lower_bound({y, -1});
            if (it != xs[x].begin()) {
                it--;
                adj_mod[i].insert(it->second);
            }
        } elif (dir[i] == '^') {
            auto it = xs[x].upper_bound({y, INF});
            if (it != xs[x].end()) {
                adj_mod[i].insert(it->second);
            }
        }
    }
    vector<ll> order;
    if (!top_sort(adj_mod, order)) {
        cout << "impossible\n";
        return 0;
    }
    cout << "possible\n";
    FORE (v, order) {
        if (v == 0) {
            continue;
        }
        if (dir[v] == '>' || dir[v] == '<') {
            cout << dir[v] << ' ' << inv[v].second << '\n';
        } else {
            cout << dir[v] << ' ' << inv[v].first << '\n';
        }
    }

    return 0;
}