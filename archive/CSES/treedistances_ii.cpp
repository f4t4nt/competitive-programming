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

void gen_tree(vector<vector<ll>> &adj, vector<vector<ll>> &children, vector<bool> &visited, ll node) {
    visited[node] = true;
    FORE (child, adj[node]) {
        if (!visited[child]) {
            children[node].pb(child);
            gen_tree(adj, children, visited, child);
        }
    }
}

void get_subtree_size(vector<vector<ll>> &children, vector<ll> &subtree_size, ll node) {
    FORE (child, children[node]) {
        get_subtree_size(children, subtree_size, child);
        subtree_size[node] += subtree_size[child];
    }
}

void solve(vector<vector<ll>> &children, vector<ll> &subtree_size, vector<ll> &rv, ll &n, ll node) {
    FORE (child, children[node]) {
        rv[child] = rv[node] + n - 2 * subtree_size[child];
        solve(children, subtree_size, rv, n, child);
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

    vector<ll> subtree_size(n, 1);
    get_subtree_size(children, subtree_size, 0);

    vector<ll> depth(n, 0);
    queue<ll> q;
    q.push(0);
    while (!q.empty()) {
        ll node = q.front();
        q.pop();
        FORE (child, children[node]) {
            depth[child] = depth[node] + 1;
            q.push(child);
        }
    }

    vector<ll> rv(n, 0);
    FORE (x, depth) {
        rv[0] += x;
    }

    solve(children, subtree_size, rv, n, 0);
    FORE (x, rv) {
        cout << x << ' ';
    }
    cout << '\n';

    return 0;
}