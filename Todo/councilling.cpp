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

// https://open.kattis.com/problems/councilling

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

    set<ll> unvisited;
    FOR (i, n) {
        unvisited.insert(i);
    }
    vector<ll> prev(n, -1), path1, path2;
    vector<bool> visited(n);
    queue<pair<ll, ll>> q;
    while (unvisited.size() > 0) {
        q.push(mp(*unvisited.begin(), -1));
        while (!q.empty()) {
            ll p, u;
            tie(u, p) = q.front();
            unvisited.erase(u);
            visited[u] = true;
            q.pop();
            prev[u] = p;
            FORE (v, adj[u]) {
                if (prev[v] == -1 && v != p) {
                    q.push(mp(v, u));
                } elif (v != p) {
                    path1.pb(v);
                    path2.pb(u);
                    break;
                }
            }
            if (!path1.empty()) {
                break;
            }
        }
        if (!path1.empty()) {
            break;
        }
    }

    if (path1.empty()) {
        cout << "IMPOSSIBLE\n";
    } else {
        ll u = path1.back();
        path1.clear();
        while (u != -1) {
            path1.pb(u);
            u = prev[u];
        }
        flip(path1);
        u = path2.back();
        path2.clear();
        while (u != -1) {
            path2.pb(u);
            u = prev[u];
        }
        flip(path2);
        ll i = 0;
        while (path1[i] == path2[i]) {
            i++;
        }
        vector<ll> cycle = {path1[i - 1]};
        FOB (j, i, sz(path1)) {
            cycle.pb(path1[j]);
        }
        for (ll j = sz(path2) - 1; j >= i; j--) {
            cycle.pb(path2[j]);
        }
        cout << sz(cycle) + 1 << '\n';
        FORE (u, cycle) {
            cout << u + 1 << ' ';
        }
        cout << cycle[0] + 1 << '\n';
    }

    return 0;
}