#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
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

vector<ll> get_path(ll src, ll snk, vector<vector<ll>> &adj, vector<vector<ll>> &dist) {
    vector<ll> path;
    ll cur = src;
    while (cur != snk) {
        path.pb(cur);
        ll nxt = -1;
        FORE (n, adj[cur]) {
            if (dist[n][snk] + dist[cur][n] == dist[cur][snk]) {
                nxt = n;
                break;
            }
        }
        cur = nxt;
    }
    path.pb(snk);
    return path;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n, m, k, src, snk;
        cin >> n >> m >> k;
        vector<tuple<ll, ll, ll>> slopes(m), lifts(k);
        vector<vector<ll>> adj_s(n), adj_l(n);
        FOR (i, m) {
            ll u, v, t;
            cin >> u >> v >> t;
            u--, v--;
            t *= -1;
            slopes[i] = {u, v, t};
            adj_s[u].pb(v);
            ssort(adj_s[u]);
        }
        FOR (i, k) {
            ll u, v, t;
            cin >> u >> v >> t;
            u--, v--;
            lifts[i] = {u, v, t};
            adj_l[u].pb(v);
            ssort(adj_l[u]);
        }
        vector<vector<ll>> dist_s(n, vector<ll>(n, 1e18)),
                            dist_l(n, vector<ll>(n, 1e18));
        FOR (i, n) {
            dist_s[i][i] = 0;
            dist_l[i][i] = 0;
        }
        FORE (slope, slopes) {
            ll u, v, t;
            tie(u, v, t) = slope;
            dist_s[u][v] = min(dist_s[u][v], t);
        }
        FORE (lift, lifts) {
            ll u, v, t;
            tie(u, v, t) = lift;
            dist_l[u][v] = min(dist_l[u][v], t);
        }
        FOR (k, n) {
            FOR (i, n) {
                FOR (j, n) {
                    dist_s[i][j] = min(dist_s[i][j], dist_s[i][k] + dist_s[k][j]);
                    dist_l[i][j] = min(dist_l[i][j], dist_l[i][k] + dist_l[k][j]);
                }
            }
        }
        ld rv = 0;
        FOR (i, n) {
            FOR (j, n) {
                if (dist_l[j][i] != 0) {
                    ld tmp = (ld) -dist_s[i][j] / dist_l[j][i];
                    if (tmp > rv) {
                        rv = tmp;
                        src = i, snk = j;
                    }
                }
            }
        }
        vector<ll> path_l = get_path(snk, src, adj_l, dist_l),
                    path_s = get_path(src, snk, adj_s, dist_s),
                    path = path_l;
        FOB (i, 1, sz(path_s)) {
            path.pb(path_s[i]);
        }
        FORE (i, path) {
            cout << i + 1 << ' ';
        }
        cout << '\n' << fixed << setprecision(10) << rv << '\n';
    }

    return 0;
}