#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

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

// https://open.kattis.com/problems/roomevacuation

ll dx[5] = {-1, 0, 1, 0, 0};
ll dy[5] = {0, -1, 0, 1, 0};

ll max_flow(ll s, ll t, vector<vector<pair<ll, ll>>> adj) {
    ll flow = 0;
    vector<ll> parent(sz(adj));
    while (true) {
        fill(parent.begin(), parent.end(), -1);
        queue<ll> q;
        q.push(s);
        parent[s] = -2;
        while (!q.empty()) {
            ll cur = q.front();
            q.pop();
            FORE (next, adj[cur]) {
                if (parent[next.first] == -1 && next.second > 0) {
                    parent[next.first] = cur;
                    q.push(next.first);
                }
            }
        }
        if (parent[t] == -1) break;
        ll path_flow = LLONG_MAX;
        for (ll cur = t; cur != s; cur = parent[cur]) {
            ll prev = parent[cur];
            FORE (next, adj[prev]) {
                if (next.first == cur) {
                    path_flow = min(path_flow, next.second);
                    break;
                }
            }
        }
        for (ll cur = t; cur != s; cur = parent[cur]) {
            ll prev = parent[cur];
            FORE (next, adj[prev]) {
                if (next.first == cur) {
                    next.second -= path_flow;
                    break;
                }
            }
            FORE (next, adj[cur]) {
                if (next.first == prev) {
                    next.second += path_flow;
                    break;
                }
            }
        }
        flow += path_flow;
    }
    return flow;
}

ll state_to_idx(bool entrance, ll x, ll y, ll t, ll &n, ll &m) {
    return (entrance ? 0 : n * m) + x * m + y + t * n * m * 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, t;
    cin >> n >> m >> t;
    vector<vector<ch>> grid(n, vector<ch>(m));
    vector<pair<ll, ll>> starts, ends;
    FOR (i, n) {
        FOR (j, m) {
            cin >> grid[i][j];
            if (grid[i][j] == 'P') {
                starts.pb({i, j});
                grid[i][j] = '.';
            } elif (grid[i][j] == 'E') {
                ends.pb({i, j});
                grid[i][j] = '.';
            }
        }
    }

    vector<vector<pair<ll, ll>>> adj(2 * n * m * (t + 1) + 2);
    // source is 2nd to last node, sink is last node
    ll source = 2 * n * m * (t + 1), sink = 2 * n * m * (t + 1) + 1;

    FORE (start, starts) {
        // source has an edge to each entrance at time 0
        adj[source].pb({state_to_idx(true, start.first, start.second, 0, n, m), 1});
        adj[state_to_idx(true, start.first, start.second, 0, n, m)].pb({source, 0});
    }

    FOR (i, t) {
        FOR (j, n) {
            FOR (k, m) {
                if (grid[j][k] != '.') {
                    continue;
                }
                FOR (l, 5) {
                    ll x = j + dx[l];
                    ll y = k + dy[l];
                    if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == '.') {
                        // each exit at time i has an edge to the entrance at time i + 1
                        adj[state_to_idx(false, j, k, i, n, m)].pb({state_to_idx(true, x, y, i + 1, n, m), 1});
                        adj[state_to_idx(true, x, y, i + 1, n, m)].pb({state_to_idx(false, j, k, i, n, m), 0});
                    }
                }
            }
        }
    }

    set<ll> test;
    FOR (i, t + 1) {
        FOR (j, n) {
            FOR (k, m) {
                // each entrance at time i has an edge to the exit at time i
                adj[state_to_idx(true, j, k, i, n, m)].pb({state_to_idx(false, j, k, i, n, m), 1});
                adj[state_to_idx(false, j, k, i, n, m)].pb({state_to_idx(true, j, k, i, n, m), 0});
                test.insert(state_to_idx(false, j, k, i, n, m));
                test.insert(state_to_idx(true, j, k, i, n, m));
            }
        }
    }
    // runtime error if encoded states are not unique
    while (sz(test) != 2 * n * m * (t + 1)) {
        continue;
    }

    FOR (i, t + 1) {
        FORE (end, ends) {
            // each exit at time i has an edge to the sink
            adj[state_to_idx(false, end.first, end.second, i, n, m)].pb({sink, 1});
            adj[sink].pb({state_to_idx(false, end.first, end.second, i, n, m), 0});
        }
    }

    cout << max_flow(source, sink, adj) << '\n';

    return 0;
}