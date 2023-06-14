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

constexpr ll INF = 1e9;

struct Edge {
    bool is_bike;
    ll v, t;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, x, y, z;
    cin >> n >> x;
    vector<vector<Edge>> adj(n);
    FOR (i, x) {
        ll u, v, t;
        cin >> u >> v >> t;
        adj[u].pb({true, v, t});
        adj[v].pb({true, u, t});
    }
    cin >> y;
    FOR (i, y) {
        ll u, v, t;
        cin >> u >> v >> t;
        adj[u].pb({false, v, t});
        adj[v].pb({false, u, t});
    }
    cin >> z;
    vector<ll> path(z + 2);
    FOR (i, z) {
        cin >> path[i + 1];
    }

    // Floyd-Warshall
    // {bike, walk}
    vector<vector<pair<ll, ll>>> dists(n, vector<pair<ll, ll>>(n, {INF, INF}));
    FOR (i, n) {
        dists[i][i] = {0, 0};
    }
    FOR (i, n) {
        FORE (e, adj[i]) {
            if (e.is_bike) {
                dists[i][e.v].first = e.t;
                dists[e.v][i].first = e.t;
            } else {
                dists[i][e.v].second = e.t;
                dists[e.v][i].second = e.t;
            }
        }
    }
    FOR (k, n) {
        FOR (i, n) {
            FOR (j, n) {
                dists[i][j].first = min(dists[i][j].first, dists[i][k].first + dists[k][j].first);
                dists[i][j].second = min(dists[i][j].second, dists[i][k].second + dists[k][j].second);
            }
        }
    }

    vector<ll> dp0(n, INF);
    dp0[0] = 0;
    FOB (i, 1, z + 2) {
        vector<ll> dp1(n, INF);
        FOR (from, n) {
            FOR (to, n) {
                if (from == to) {
                    dp1[to] = min(dp1[to], dp0[from] + dists[path[i - 1]][path[i]].second);
                } else {
                    dp1[to] = min(dp1[to],
                            dp0[from] +
                            dists[path[i - 1]][from].second +
                            dists[from][to].first +
                            dists[to][path[i]].second);
                }
            }
        }
        dp0 = dp1;
    }
    cout << dp0[0] << '\n';

    return 0;
}