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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    vector<pair<ll, ll>> edges(m);
    vector<vector<ll>> adj(n);
    FOR (i, m) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        edges[i] = mp(a, b);
        adj[a].pb(b);
        adj[b].pb(a);
    }

    ll uncolored = n;
    vector<ll> color(n, 0);
    bool bipartite = true;
    while (uncolored > 0 && bipartite) {
        queue<ll> q;
        ll start = 0;
        while (color[start] != 0) {
            start++;
        }
        q.push(start);
        color[start] = 1;
        while (!q.empty()) {
            ll u = q.front();
            uncolored--;
            q.pop();
            FORE (v, adj[u]) {
                if (color[v] == 0) {
                    color[v] = 3 - color[u];
                    q.push(v);
                } elif (color[v] == color[u]) {
                    bipartite = false;
                    break;
                }
            }
        }
    }

    if (bipartite) {
        FOR (i, n) {
            cout << color[i] << ' ';
        }
        cout << '\n';
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}