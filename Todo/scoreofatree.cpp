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

// https://codeforces.com/contest/1777/problem/D

constexpr ll MOD = 1e9 + 7;

vector<ll> pow2(2e5 + 1, 1);

ll sim(ll &n, vector<ll> values, vector<vector<ll>> &children) {
    ll rv = 0, cv = 0;
    FOR (i, n) {
        cv += values[i];
    }

    while (cv > 0) {
        rv = (rv + cv) % MOD;
        cv = 0;
        vector<ll> new_values(n);
        FOR (i, n) {
            FORE (c, children[i]) {
                new_values[i] ^= values[c];
            }
        }
        values = new_values;
        FOR (i, n) {
            cv += values[i];
        }
    }

    return rv;
}

ll bruteforce(ll &n, vector<vector<ll>> &children) {
    ll rv = 0;
    vector<ll> seed(n);
    pair<ll, ll> rv_pair = {0, 0};

    FOR (i, 1 << n) {
        FOR (j, n) {
            seed[j] = (i >> j) & 1;
        }
        ll tv = sim(n, seed, children);
        rv = (rv + tv) % MOD;
        if (seed[0] == 0) {
            rv_pair.first = (rv_pair.first + tv) % MOD;
        } else {
            rv_pair.second = (rv_pair.second + tv) % MOD;
        }
    }

    cout << rv_pair.first << ' ' << rv_pair.second << '\n';
    return rv;
}

ll solve(ll node, vector<vector<ll>> &children, vector<ll> &size) {
    // if (sz(children[node]) == 0) {
    //     return 1;
    // }
    vector<ll> child_values;
    FOR (i, sz(children[node])) {
        child_values.pb(solve(children[node][i], children, size));
    }
    ll rv = pow2[size[node] - 1];
    FOR (i, sz(child_values)) {
        rv = (rv + child_values[i] * pow2[size[node] - 1 - size[children[node][i]]]) % MOD;
    }
    return (2 * rv + pow2[size[node] - 1]) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    FOB (i, 1, sz(pow2)) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }

    ll t;
    cin >> t;
    
    while (t--) {
        ll n;
        cin >> n;
        vector<pair<ll, ll>> edges(n - 1);
        vector<ll> parent(n, -1), depth(n), size(n);
        vector<vector<ll>> adj(n), children(n);
        vector<bool> visited(n);
        FOR(i, n - 1) {
            cin >> edges[i].first >> edges[i].second;
            edges[i].first--, edges[i].second--;
            adj[edges[i].first].pb(edges[i].second);
            adj[edges[i].second].pb(edges[i].first);
        }

        function<void(ll, ll)> dfs = [&](ll u, ll p) {
            visited[u] = true;
            parent[u] = p;
            depth[u] = p == -1 ? 0 : depth[p] + 1;
            size[u] = 1;
            FORE(v, adj[u]) {
                if (!visited[v]) {
                    dfs(v, u);
                    children[u].pb(v);
                    size[u] += size[v];
                }
            }
        };
        dfs(0, -1);

        // cout << bruteforce(n, children) << '\n';
        cout << solve(0, children, size) / 2 << '\n';
    }

    return 0;
}