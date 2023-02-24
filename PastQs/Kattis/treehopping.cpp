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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;

    while (t--) {
        ll n;
        cin >> n;
        vector<pair<ll, ll>> edges(n - 1);
        vector<vector<ll>> adj(n);
        FOR(i, n - 1) {
            cin >> edges[i].first >> edges[i].second;
            edges[i].first--, edges[i].second--;
            adj[edges[i].first].pb(edges[i].second);
            adj[edges[i].second].pb(edges[i].first);
        }
        vector<ll> parent(n, -1), depth(n);
        queue<ll> q;
        q.push(0);
        while (!q.empty()) {
            ll v = q.front();
            q.pop();
            FORE(u, adj[v]) {
                if (u != parent[v]) {
                    parent[u] = v;
                    depth[u] = depth[v] + 1;
                    q.push(u);
                }
            }
        }
        vector<ll> p(n);
        FOR (i, n) {
            cin >> p[i];
            p[i]--;
        }
        ll rv = 1;
        FOB (i, 1, n) {
            ll cnt = 0;
            ll a = p[i - 1], b = p[i];
            while (cnt < 3 && a != b) {
                if (depth[a] > depth[b]) {
                    a = parent[a];
                } else {
                    b = parent[b];
                }
                cnt++;
            }
            if (a != b) {
                rv = 0;
                break;
            }
        }
        cout << rv << '\n';
    }

    return 0;
}