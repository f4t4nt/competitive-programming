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

constexpr ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<ll> parent(n), in(n);
    vector<vector<ll>> children(n);
    FOR (i, n) {
        cin >> parent[i];
        parent[i]--;
        in[parent[i]]++;
        children[parent[i]].pb(i);
    }
    // cycle id, distance from cycle
    ll curr_id = 0;
    vector<pair<ll, ll>> dist(n, {-1, -1});
    FOR (i, n) {
        if (dist[i].first != -1) {
            continue;
        }
        ll v = i;
        vector<ll> path;
        while (dist[v].first == -1) {
            path.pb(v);
            dist[v].first = -2;
            v = parent[v];
        }
        if (dist[v].first == -2) {
            ll j = sz(path) - 1;
            while (path[j] != v) {
                dist[path[j]] = {curr_id, 0};
                j--;
            }
            ll d = 0;
            while (j >= 0) {
                dist[path[j]] = {curr_id, d};
                j--;
                d++;
            }
            curr_id++;
        } else {
            ll j = sz(path) - 1,
                id = dist[v].first,
                d = dist[v].second;
            while (j >= 0) {
                d++;
                dist[path[j]] = {id, d};
                j--;
            }
        }
    }

    queue<ll> q;
    FOR (i, n) {
        if (in[i] == 0) {
            q.push(i);
        }
    }

    vector<ll> f(n, 1);
    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        FORE (u, children[v]) {
            f[v] = (f[v] * f[u]) % MOD;
        }
        f[v] = (f[v] + 1) % MOD;
        in[parent[v]]--;
        if (in[parent[v]] == 0) {
            q.push(parent[v]);
        }
    }

    vector<ll> g(curr_id, 1);
    FOR (i, n) {
        if (dist[i].second == 1) {
            g[dist[i].first] = (g[dist[i].first] * f[i]) % MOD;
        }
    }

    ll rv = 1;
    FOR (i, sz(g)) {
        rv = (rv * (g[i] + 1)) % MOD;
    }
    rv = (rv + MOD - 1) % MOD;
    cout << rv << '\n';

    return 0;
}