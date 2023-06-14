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

pair<ll, ll> solve(ll node, vector<vector<ll>> &children) {
    if (sz(children[node]) == 0) {
        return mp(0, 0);
    }
    vector<pair<ll, ll>> child_values;
    FORE (child, children[node]) {
        child_values.pb(solve(child, children));
    }
    pair<ll, ll> rv = mp(0, 0);
    FORE (child_value, child_values) {
        rv.first += max(child_value.first, child_value.second);
    }
    FOR (i, sz(child_values)) {
        ll tmp = 1 + rv.first - max(child_values[i].first, child_values[i].second) + child_values[i].first;
        rv.second = max(rv.second, tmp);
    }
    return rv;
}

void gen_tree(vector<vector<ll>> &adj, vector<vector<ll>> &children, vector<bool> &visited, ll node) {
    visited[node] = true;
    FORE (child, adj[node]) {
        if (!visited[child]) {
            children[node].pb(child);
            gen_tree(adj, children, visited, child);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    vector<pair<ll, ll>> edges(n - 1);
    vector<vector<ll>> adj(n);
    FOR (i, n - 1) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        edges[i] = mp(a, b);
        adj[a].pb(b);
        adj[b].pb(a);
    }

    vector<vector<ll>> children(n);
    vector<bool> visited(n, false);
    gen_tree(adj, children, visited, 0);

    pair<ll, ll> rv = solve(0, children);
    cout << max(rv.first, rv.second) << '\n';

    return 0;
}