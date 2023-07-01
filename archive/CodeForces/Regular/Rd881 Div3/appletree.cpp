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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<vector<ll>> adj(n);
        FOR (i, n - 1) {
            ll u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vector<ll> children(n), leafs(n);
        function<void(ll, ll)> dfs = [&](ll u, ll p) {
            children[u] = 1;
            leafs[u] = 0;
            FORE (v, adj[u]) {
                if (v != p) {
                    dfs(v, u);
                    children[u] += children[v];
                    leafs[u] += leafs[v];
                }
            }
            if (children[u] == 1) {
                leafs[u] = 1;
            }
        };
        dfs(0, -1);
        ll q;
        cin >> q;
        while (q--) {
            ll u, v;
            cin >> u >> v;
            u--, v--;
            cout << leafs[u] * leafs[v] << '\n';
        }
    }

    return 0;
}