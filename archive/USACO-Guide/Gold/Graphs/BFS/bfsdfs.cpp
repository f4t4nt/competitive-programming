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

// https://csacademy.com/contest/archive/task/bfs-dfs

int main() {
    ll n, rv = 0;
    cin >> n;
    vector<vector<ll>> g(n);
    vector<ll> bfs(n), dfs(n);
    FOR(i, n) {
        cin >> bfs[i];
        bfs[i]--;
    }
    FOR(i, n) {
        cin >> dfs[i];
        dfs[i]--;
    }
    if (bfs[1] != dfs[1]) {
        cout << -1 << '\n';
        return 0;
    }
    FOB(i, 1, n) {
        g[0].pb(bfs[i]);
        g[bfs[i]].pb(0);
    }
    FOB(i, 2, n) {
        g[dfs[i - 1]].pb(dfs[i]);
        g[dfs[i]].pb(dfs[i - 1]);
    }
    FOR(i, n) rv += g[i].size();
    cout << rv / 2 << '\n';
    FOR(i, n) {
        FORE(j, g[i]) {
            if(j > i) cout << i + 1 << " " << j + 1 << '\n';
        }
    }
    return 0;
}