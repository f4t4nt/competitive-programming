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

struct Point {
    ll x, y;
};

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<Point> p(n);
    vector<vector<pair<ll, ll>>> adj(2 * m + 2);
    FOR (i, m) {
        adj[2 * m].pb({i, 1});
        adj[i].pb({2 * m, 0});
        adj[i + m].pb({2 * m + 1, 1});
        adj[2 * m + 1].pb({i + m, 0});
    }
    FOR (i, n) {
        cin >> p[i].x >> p[i].y;
        adj[p[i].x].pb({m + p[i].y, 1});
        adj[m + p[i].y].pb({p[i].x, 0});
    }

    cout << max_flow(2 * m, 2 * m + 1, adj) << '\n';

    return 0;
}