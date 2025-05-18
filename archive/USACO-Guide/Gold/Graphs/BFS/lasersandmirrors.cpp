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

// http://www.usaco.org/index.php?page=viewproblem2&cpid=671

int main() {
    ifstream cin("lasers.in");
    ofstream cout("lasers.out");

    ll n, xl, yl, xb, yb;
    cin >> n >> xl >> yl >> xb >> yb;
    vector<map<ll, vector<ll>>> g(2);
    vector<map<ll, ll>> d(2);
    queue<pair<ll, ll>> bfs;
    bfs.push(mp(0, xl));
    bfs.push(mp(1, yl));
    g[0][xl].pb(yl);
    g[0][xb].pb(yb);
    g[1][yl].pb(xl);
    g[1][yb].pb(xb);
    d[0][xl] = 1;
    d[1][yl] = 1;
    FOR(i, n) {
        ll x, y;
        cin >> x >> y;
        g[0][x].pb(y);
        g[1][y].pb(x);
    }
    while(sz(bfs)) {
        ll i = bfs.front().first, j = bfs.front().second;
        bfs.pop();
        FORE(k, g[i][j]) {
            if(!d[1 - i][k]) {
                d[1 - i][k] = d[i][j] + 1;
                bfs.push(mp(1 - i, k));
            }
        }
    }
    cout << min(d[0][xb], d[1][yb]) - 1 << '\n';
    return 0;
}