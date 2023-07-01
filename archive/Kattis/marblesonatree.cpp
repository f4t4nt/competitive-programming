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

struct LCA_Tree {
    vector<vector<ll>> parent, adj;
    vector<ll> pre, post, depth;
    ll n, timer;

    LCA_Tree(ll &n0, vector<vector<ll>> &adj0) {
        n = n0;
        timer = 0;
        pre = vector<ll>(n), post = pre, depth = pre;
        parent = vector<vector<ll>>(n, vector<ll>(30));
        adj = adj0;
        dfs(0, 0, 0);
        gen();
    }

    void dfs(ll node, ll par, ll d) {
        pre[node] = timer++;
        depth[node] = d;
        parent[node][0] = par;
        FORE (child, adj[node]) {
            if (child != par) {
                dfs(child, node, d + 1);
            }
        }
        post[node] = timer++;
    }

    void gen() {
        FOR (i, 29) {
            FOR (j, n) {
                parent[j][i + 1] = parent[parent[j][i]][i];
            }
        }
    }

    bool is_anc(ll u, ll v) {
        return pre[u] <= pre[v] && post[u] >= post[v];
    }

    ll lca(ll u, ll v) {
        if (is_anc(u, v)) return u;
        if (is_anc(v, u)) return v;
        FORR (i, 30) {
            if (!is_anc(parent[u][i], v)) {
                u = parent[u][i];
            }
        }
        return parent[u][0];
    }

    ll dist(ll u, ll v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    bool disjoint(vector<pair<ll, ll>> paths) {
        vector<pair<ll, ll>> p;
        FORE (path, paths) {
            ll u, v;
            tie(u, v) = path;
            ll w = lca(u, v);
            p.pb({w, u});
            p.pb({w, v});
        }
        FOR (i, sz(p)) {
            FOR (j, i - i % 2) {
                if (!(lca(p[i].second, p[j].first) != p[j].first ||
                    lca(p[j].second, p[i].first) != p[i].first))
                {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ll n;
        cin >> n;
        if (n == 0) {
            break;
        }
        vector<ll> par(n), deg(n), cnt(n);
        FOR (i, n) {
            ll v, m, d;
            cin >> v >> m >> d;
            v--;
            cnt[v] = m;
            deg[v] = d;
            FOR (j, d) {
                ll u;
                cin >> u;
                u--;
                par[u] = v;
            }
        }
        queue<ll> q;
        FOR (i, n) {
            if (deg[i] == 0) {
                q.push(i);
            }
        }
        ll rv = 0;
        while (!q.empty()) {
            ll v = q.front();
            q.pop();
            if (par[v] != v) {
                ll u = par[v];
                deg[u]--;
                if (deg[u] == 0) {
                    q.push(u);
                }
                ll diff = cnt[v] - 1;
                cnt[u] += diff;
                rv += abs(diff);
            }
        }
        cout << rv << '\n';
    }

    return 0;
}