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

// http://www.usaco.org/index.php?page=viewproblem2&cpid=1090

int main() {
    ll n, k;
    cin >> n >> k;
    vector<ll> b(n);
    FOR(i, n) {
        cin >> b[i];
    }
    vector<vector<bool>> s(k + 1, vector<bool>(k + 1));
    FOB(i, 1, k + 1) {
        FOB(j, 1, k + 1) {
            char c;
            cin >> c;
            s[i][j] = c == '1';
        }
    }
    s[0] = s[b[0]];
    b[0] = 0;
    vector<vector<ll>> dist(k + 1, vector<ll>(n, 1e18));
    deque<pair<ll, ll>> q;
    q.push_back({0, 0});
    dist[0][0] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop_front();
        if (y + 1 < n && dist[x][y + 1] > dist[x][y] + 1) {
            dist[x][y + 1] = dist[x][y] + 1;
            q.push_back({x, y + 1});
        }
        if (y - 1 >= 0 && dist[x][y - 1] > dist[x][y] + 1) {
            dist[x][y - 1] = dist[x][y] + 1;
            q.push_back({x, y - 1});
        }
        if (s[x][b[y]] && dist[b[y]][y] > dist[x][y]) {
            dist[b[y]][y] = dist[x][y];
            q.push_front({b[y], y});
        }
    }
    if (dist[b[n - 1]][n - 1] == 1e18) {
        cout << -1;
    } else {
        cout << dist[b[n - 1]][n - 1];
    }
    cout << '\n';
    return 0;
}