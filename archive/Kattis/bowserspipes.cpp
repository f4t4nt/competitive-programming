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

constexpr ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, t, cnt = 0;
    cin >> n;
    vector<ll> f(n), g(n, -1);
    vector<vector<ll>> adj_rev(n);
    FOR (i, n) {
        cin >> f[i];
        if (f[i] != -1) {
            adj_rev[f[i]].pb(i);
        } else {
            g[i] = cnt++;
        }
    }

    vector<ll> rv(cnt);
    vector<bool> vis(n, false);
    FOR (i, n) {
        if (vis[i] || g[i] == -1) {
            continue;
        }
        pair<ll, ll> best = {n, -1};
        queue<pair<ll, ll>> bfs;
        bfs.push({i, 0});
        while (!bfs.empty()) {
            ll u, d;
            tie(u, d) = bfs.front();
            bfs.pop();
            if (vis[u]) {
                continue;
            }
            vis[u] = true;
            g[u] = g[i];
            if (adj_rev[u].empty()) {
                best = min(best, {d, u});
            }
            FORE (v, adj_rev[u]) {
                bfs.push({v, d + 1});
            }
        }
        rv[g[i]] = best.second;
    }

    cin >> t;
    while (t--) {
        ll x;
        cin >> x;
        cout << rv[g[x]] << '\n';
    }

    return 0;
}