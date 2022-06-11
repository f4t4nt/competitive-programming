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

// https://cses.fi/problemset/task/1707/

ll girth(ll &i, ll &n, ll &m, vector<vector<ll>> &g) {
    ll rv = 1e18;
    queue<ll> bfs;
    vector<ll> d(n, -1);
    bfs.push(i);
    d[i] = 0;
    while(sz(bfs)) {
        ll j = bfs.front();
        bfs.pop();
        if (d[j] > rv / 2) break;
        FORE(k, g[j]) {
            if(d[k] == -1) {
                d[k] = d[j] + 1;
                bfs.push(k);
            } else if(d[k] == d[j]) {
                rv = min(rv, d[k] * 2 + 1);
            } else if(d[k] == d[j] + 1) {
                rv = min(rv, d[k] * 2);
            }
        }
    }
    return rv;
}

int main() {
    ll n, m, rv = 1e18;
    cin >> n >> m;
    vector<vector<ll>> g(n);
    FOR(i, m) {
        ll a, b;
        cin >> a >> b;
        g[a - 1].pb(b - 1);
        g[b - 1].pb(a - 1);
    }
    FOR(i, n) rv = min(rv, girth(i, n, m, g));
    if(rv == 1e18) cout << -1 << '\n';
    else cout << rv << '\n';
    return 0;
}