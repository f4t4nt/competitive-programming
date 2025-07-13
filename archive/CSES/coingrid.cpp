#include <bits/stdc++.h>
using namespace std;
 
typedef __int128 i128;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;
 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
#include <bits/extc++.h>
using namespace __gnu_pbds;
 
template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
// s.order_of_key(x) -> number of elements < x
// s.find_by_order(x) -> iterator to the x-th element (0-indexed)
 
#pragma GCC target("popcnt,lzcnt")
// __builtin_popcount(x) -> number of set bits
// __builtin_clz(x) -> number of leading zeros
// for ll, use __builtin_popcountll, __builtin_clzll
 
#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
// #define f first
// #define s second
 
#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif
 
// Hopcroft-Karp: maximum matching in a bipartite graph
// - LHS nodes: 0 .. nL-1
// - RHS nodes: 0 .. nR-1
// - adj[u]   : list of neighbours of u in LHS
// Worst case time complexity: O(E * sqrt(V))
struct HopcroftKarp {
    ll nL, nR;
    vector<vector<ll>> &adj;
 
    vector<ll> match_l, match_r;    // LHS -> RHS, RHS -> LHS (-1 = free)
    vector<ll> dist;                // BFS levels
    queue<ll> q;
 
    explicit HopcroftKarp(vector<vector<ll>> &_adj,
                          ll _nL, ll _nR)
        : nL(_nL), nR(_nR), adj(_adj),
          match_l(nL, -1), match_r(nR, -1),
          dist(nL) {}
 
    // BFS builds alternating-level graph; returns true if free RHS reachable
    bool bfs() {
        while (!q.empty()) q.pop();
        for (ll u = 0; u < nL; u++) {
            if (match_l[u] == -1) dist[u] = 0, q.push(u);
            else                  dist[u] = -1;
        }
        bool reachable = false;
        while (!q.empty()) {
            ll u = q.front(); q.pop();
            for (ll v : adj[u]) {
                ll nxt = match_r[v];
                if (nxt != -1 && dist[nxt] == -1) {
                    dist[nxt] = dist[u] + 1;
                    q.push(nxt);
                }
                if (nxt == -1) reachable = true;    // an unmatched RHS exists
            }
        }
        return reachable;
    }
 
    // DFS searches for augmenting paths within BFS levels
    bool dfs(ll u) {
        for (ll v : adj[u]) {
            ll nxt = match_r[v];
            if (nxt == -1 || (dist[nxt] == dist[u] + 1 && dfs(nxt))) {
                match_l[u] = v;
                match_r[v] = u;
                return true;
            }
        }
        dist[u] = -1;   // block useless nodes
        return false;
    }
 
    ll solve() {
        ll matched = 0;
        // optional greedy pre-match (improves running time in dense graphs)
        for (ll u = 0; u < nL; u++) if (match_l[u] == -1)
            for (ll v : adj[u]) if (match_r[v] == -1) {
                match_l[u] = v;
                match_r[v] = u;
                matched++; break;
            }
 
        // Hopcroft-Karp phases
        while (bfs()) {
            for (ll u = 0; u < nL; u++)
                if (match_l[u] == -1 && dfs(u))
                    matched++;
            if (matched == min(nL, nR)) break;   // perfect => done
        }
        return matched;
    }
};
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
 
    ll n; cin >> n;
    vector<str> grid(n);
    for (str &row : grid) cin >> row;
    vector<vector<ll>> adj(n);
    for (ll i = 0; i < n; i++)
        for (ll j = 0; j < n; j++)
            if (grid[i][j] == 'o')
                adj[i].pb(j);
    HopcroftKarp hk(adj, n, n);
    cout << hk.solve() << '\n';
    vector<bool> visL(n, 0), visR(n, 0);
    queue<ll> q;
    for (ll u = 0; u < n; u++)
        if (hk.match_l[u] == -1) {
            visL[u] = true;
            q.push(u);
        }
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        for (ll v : adj[u]) {
            if (hk.match_l[u] != v && !visR[v]) {
                visR[v] = true;
                ll w = hk.match_r[v];
                if (w != -1 && !visL[w]) {
                    visL[w] = 1;
                    q.push(w);
                }
            }
        }
    }
    vector<pll> moves;
    for (ll i = 0; i < n; i++)
        if (!visL[i] && !adj[i].empty()) moves.pb({1, i+1});
    for (ll j = 0; j < n; j++)
        if (visR[j]) moves.pb({2, j + 1});
    for (auto [t, x] : moves) cout << t << ' ' << x << '\n';
 
    return 0;
}
