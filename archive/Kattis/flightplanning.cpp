#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;
 
#pragma GCC target("popcnt,lzcnt")
 
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

// imma show YOU how great i am.

void mark(ll u, ll p, ll m, vector<ll> &marks, vector<vector<ll>> &adj) {
    marks[u] = m;
    FORE (v, adj[u]) {
        if (v != p) {
            mark(v, u, m, marks, adj);
        }
    }
}

vector<pair<ll, ll>> get_centers(ll n, ll cnt, vector<ll> deg, vector<ll> &marks, vector<vector<ll>> &adj) {
    vector<pair<ll, ll>> rv;
    while (cnt--) {
        ll total = 0;
        vector<ll> q0, q1;
        bool skip = false;
        FOR (j, n) {
            if (marks[j] == cnt) {
                total++;
                if (deg[j] == 1) {
                    q0.pb(j);
                } elif (deg[j] == 0) {
                    rv.pb({j, 0});
                    skip = true;
                    break;
                }
            }
        }
        if (skip) {
            continue;
        }
        vector<bool> vis(n);
        ll dist = 0;
        while (total > 2) {
            dist += 2;
            FORE (u, q0) {
                vis[u] = true;
                FORE (v, adj[u]) {
                    if (marks[v] == cnt) {
                        deg[v]--;
                        if (deg[v] <= 1 && !vis[v]) {
                            q1.pb(v);
                        }
                    }
                }
                total--;
            }
            q0.clear();
            swap(q0, q1);
        }
        if (total == 2) {
            dist++;
        }
        rv.pb({q0[0], dist});
    }
    return rv;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;
    vector<pair<ll, ll>> edges;
    vector<vector<ll>> adj(n);
    vector<ll> deg(n), marks(n);
    FOR (i, n - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
        edges.pb({u, v});
        deg[u]++, deg[v]++;
    }
    ll rv = 1e18;
    pair<ll, ll> e[2];
    for (auto [u, v] : edges) {
        deg[u]--, deg[v]--;
        mark(u, v, 0, marks, adj);
        mark(v, u, 1, marks, adj);
        auto centers = get_centers(n, 2, deg, marks, adj);
        ll &w1 = centers[0].second, &w2 = centers[1].second;
        ll tmp = max({w1, w2, (w1 + 1) / 2 + (w2 + 1) / 2 + 1});
        if (tmp < rv) {
            rv = tmp;
            e[0] = {u, v};
            e[1] = {centers[0].first, centers[1].first};
        }
        deg[u]++, deg[v]++;
    }
    cout << rv << '\n';
    cout << e[0].first + 1 << ' ' << e[0].second + 1 << '\n';
    cout << e[1].first + 1 << ' ' << e[1].second + 1 << '\n';

    return 0;
}