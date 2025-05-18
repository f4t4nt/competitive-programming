#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<vector<ll>> pref(3, vector<ll>(n));
        FOR (k, 3) FOR (i, n) {
            cin >> pref[k][i];
            pref[k][i]--;
        }
        vector<map<ll, ll>> adj(n);
        FOR (k, 3) {
            auto &ord = pref[k];
            pll mn = {n, n};
            FORR (i, n) {
                if (ord[i] > mn.f && !adj[i].count(mn.s)) adj[i][mn.s] = k;
                mn = min(mn, {ord[i], i});
            }
            for (ll d = 1; d < 18; d++) FOR (i, n - d) if (ord[i] > ord[i + d] && !adj[i].count(i + d)) adj[i][i + d] = k;
        }
        vector<pll> par(n, {-1, -1});
        queue<ll> bfs;
        bfs.push(0);
        while (!bfs.empty()) {
            ll u = bfs.front();
            bfs.pop();
            for (auto [v, k] : adj[u]) {
                if (par[v].f == -1) {
                    par[v] = {u, k};
                    bfs.push(v);
                }
            }
        }
        if (par[n - 1].f == -1) cout << "NO\n";
        else {
            cout << "YES\n";
            vector<pll> res;
            ll u = n - 1;
            while (u != -1) {
                res.pb({par[u].s, u});
                u = par[u].f;
            }
            res.pop_back();
            flip(res);
            cout << sz(res) << '\n';
            for (auto [k, v] : res) cout << "qkj"[k] << ' ' << v + 1 << '\n';
        }
    }

    return 0;
}