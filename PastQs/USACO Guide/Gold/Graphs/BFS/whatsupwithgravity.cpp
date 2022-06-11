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

// http://www.usaco.org/index.php?page=viewproblem2&cpid=282

int main() {
    ifstream cin("gravity.in");
    ofstream cout("gravity.out");

    ll n, m;
    cin >> n >> m;
    vector<string> grid(n);
    FOR(i, n) cin >> grid[i];
    vector<vector<vector<ll>>> ref(2, vector<vector<ll>>(n, vector<ll>(m, 1e18)));
    set<tuple<ll, ll, ll, ll>> bfs;
    pair<ll, ll> d;
    FOR(i, n) FOR(j, m) {
        if(grid[i][j] == 'C') {
            ref[1][i][j] = 0;
            bfs.insert(mt(0, 1, i, j));
        } elif(grid[i][j] == 'D') d = mp(i, j);
    }
    while(sz(bfs) && ref[0][d.first][d.second] == 1e18 && ref[0][d.first][d.second] == 1e18) {
        auto tmp = *bfs.begin();
        bfs.erase(bfs.begin());
        ll d = get<0>(tmp),
            x = get<1>(tmp),
            i = get<2>(tmp),
            j = get<3>(tmp),
            g = 2 * x - 1;
        if(i + g >= 0 && i + g < n && grid[i + g][j] != '#') {
            if(ref[x][i + g][j] > ref[x][i][j]) {
                ref[x][i + g][j] = ref[x][i][j];
                bfs.insert(mt(d, x, i + g, j));
            }
        } elif(i + g >= 0 && i + g < n) {
            if(j < m - 1 && grid[i][j + 1] != '#' && ref[x][i][j + 1] > ref[x][i][j]) {
                ref[x][i][j + 1] = ref[x][i][j];
                bfs.insert(mt(d, x, i, j + 1));
            }
            if(j > 0 && grid[i][j - 1] != '#' && ref[x][i][j - 1] > ref[x][i][j]) {
                ref[x][i][j - 1] = ref[x][i][j];
                bfs.insert(mt(d, x, i, j - 1));
            }
            if(ref[1 - x][i][j] > ref[x][i][j] + 1) {
                ref[1 - x][i][j] = ref[x][i][j] + 1;
                bfs.insert(mt(d + 1, 1 - x, i, j));
            }
        }
    }
    // FOR(i, n) {
    //     FOR(j, m) {
    //         if(ref[0][i][j] == 1e18 && ref[1][i][j] == 1e18) cout << grid[i][j];
    //         else cout << (ch) ('0' + min(ref[0][i][j], ref[1][i][j]));
    //     }
    //     cout << '\n';
    // }
    // cout << '\n';
    if(ref[0][d.first][d.second] == 1e18 && ref[0][d.first][d.second] == 1e18) cout << "-1\n";
    else cout << min(ref[0][d.first][d.second], ref[1][d.first][d.second]) << '\n';
    return 0;
}