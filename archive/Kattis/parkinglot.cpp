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

    vector<vector<pair<ll, ld>>> adj((n + 1) * (m + 1));
    for (ld i0 = 0; i0 <= n; i0 += 1) {
        for (ld j0 = 0; j0 <= m; j0 += 1) {
            for (ld i1 = 0; i1 <= n; i1 += 1) {
                for (ld j1 = 0; j1 <= m; j1 += 1) {
                    if (i0 == i1 && j0 == j1) {
                        continue;
                    }
                    bool ok = true;
                    // check if there is any occupied cell between the POINTS (i0, j0) and (i1, j1)
                    ld x = i0, y = j0;
                    ld dx = (i1 - i0) / (ld) (abs(i1 - i0) + abs(j1 - j0));
                    ld dy = (j1 - j0) / (ld) (abs(i1 - i0) + abs(j1 - j0));
                    while (abs(x - i1) > 1e-9 && abs(y - j1) > 1e-9) {
                        x += dx;
                        y += dy;
                        if (x - (ll) x <= 1e-9 || y - (ll) y <= 1e-9) {
                            continue;
                        }
                        if (grid[(ll) x][(ll) y] == '#') {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        ld dist = sqrt((i1 - i0) * (i1 - i0) + (j1 - j0) * (j1 - j0));
                        adj[i0 * (m + 1) + j0].pb({i1 * (m + 1) + j1, dist});
                    }
                }
            }
        }
    }

    // dijkstra from (0, 0) to (n, m)
    vector<ld> dist((n + 1) * (m + 1), 1e18);
    dist[0] = 0;
    priority_queue<pair<ld, ll>, vector<pair<ld, ll>>, greater<>> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        ld d, u;
        tie(d, u) = pq.top();
        pq.pop();
        if (d > dist[u]) {
            continue;
        }
        FORE (v, adj[u]) {
            if (dist[u] + v.second < dist[v.first]) {
                dist[v.first] = dist[u] + v.second;
                pq.push({dist[v.first], v.first});
            }
        }
    }
    cout << fixed << setprecision(10) << dist[(n + 1) * (m + 1) - 1] << '\n';

    return 0;
}