#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <list>
#include <map>
#include <math.h>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <string.h>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

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

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
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

// http://www.usaco.org/index.php?page=viewproblem2&cpid=491

struct Node {
    ll idx;
    vector<ll> dist = vector<ll>(3, 1e18); // 0 - bessie, 1 - elsie, 2 - both
    vector<ll> adj;
};

int main() {
    ifstream cin("piggyback.in");
    ofstream cout("piggyback.out");
    vector<ll> energies(3);
    ll n, m;
    cin >> energies[0] >> energies[1] >> energies[2] >> n >> m;
    vector<Node> nodes(n);
    FOR(i, n) {
        nodes[i].idx = i;
    }
    FOR(i, m) {
        ll a, b;
        cin >> a >> b;
        a--;
        b--;
        nodes[a].adj.pb(b);
        nodes[b].adj.pb(a);
    }
    queue<tuple<ll, ll, ll>> bfs; // idx, dist, type
    nodes[0].dist[0] = 0;
    nodes[1].dist[1] = 0;
    nodes[n - 1].dist[2] = 0;
    bfs.push(mt(0, 0, 0));
    bfs.push(mt(1, 0, 1));
    bfs.push(mt(n - 1, 0, 2));
    while (!bfs.empty()) {
        auto [idx, dist, type] = bfs.front();
        bfs.pop();
        FORE(adj, nodes[idx].adj) {
            if (nodes[adj].dist[type] > dist + 1) {
                nodes[adj].dist[type] = dist + 1;
                bfs.push(mt(adj, dist + 1, type));
            }
        }
    }
    ll rv = 1e18;
    FORE(node, nodes) {
        rv = min(rv, node.dist[0] * energies[0] + node.dist[1] * energies[1] + node.dist[2] * energies[2]);
    }
    cout << rv << '\n';
    return 0;
}