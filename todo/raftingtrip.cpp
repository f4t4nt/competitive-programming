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

// https://open.kattis.com/submissions/10515365

ll dx[] = {1, 0, -1, 0};
ll dy[] = {0, 1, 0, -1};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<vector<ch>> grid(n, vector<ch>(m));
    FOR (i, n) {
        FOR (j, m) {
            cin >> grid[i][j];
        }
    }

    vector<ll> in(n * m);
    vector<vector<ll>> adj(n * m);
    FOR (i, n) {
        FOR (j, m) {
            if (grid[i][j] == '<' && i * m + j - 1 >= 0) {
                in[i * m + j - 1]++;
                adj[i * m + j].pb(i * m + j - 1);
            } elif (grid[i][j] == '>' && i * m + j + 1 < n * m) {
                in[i * m + j + 1]++;
                adj[i * m + j].pb(i * m + j + 1);
            } elif (grid[i][j] == '^' && (i - 1) * m + j >= 0) {
                in[(i - 1) * m + j]++;
                adj[i * m + j].pb((i - 1) * m + j);
            } elif (grid[i][j] == 'v' && (i + 1) * m + j < n * m) {
                in[(i + 1) * m + j]++;
                adj[i * m + j].pb((i + 1) * m + j);
            }
        }
    }

    queue<ll> q;
    FOR (i, n * m) {
        if (in[i] == 0) {
            q.push(i);
        }
    }

    vector<bool> vis(n * m);
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        FORE (v, adj[u]) {
            in[v]--;
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }

    // for each node, if it is not visited, and is not # or ., then it is part of a cycle
    vector<ll> cycle_ids;
    FOR (i, n * m) {
        if (vis[i] || grid[i / m][i % m] == '#' || grid[i / m][i % m] == '.') {
            continue;
        }
        vector<ll> cycle;
        ll u = i;
        set<ll> visited_sights;
        while (!vis[u]) {
            FOR (j, 4) {
                ll x = u / m + dx[j];
                ll y = u % m + dy[j];
                if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == '#') {
                    visited_sights.insert(x * m + y);
                }
            }
            vis[u] = true;
            cycle.pb(u);
            u = adj[u][0];
        }
        
    }

    return 0;
}