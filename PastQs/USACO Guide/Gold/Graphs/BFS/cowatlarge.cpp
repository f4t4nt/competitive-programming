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

// http://www.usaco.org/index.php?page=viewproblem2&cpid=790

int main() {
    ifstream cin("atlarge.in");
    ofstream cout("atlarge.out");

    ll n, k;
    cin >> n >> k;
    k--;
    vector<vector<ll>> g(n);
    FOR(i, n - 1) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        g[a].pb(b);
        g[b].pb(a);
    }
    ll x = 1;
    set<ll> rv;
    vector<ll> ref(n);
    queue<ll> bfs;
    FOR(i, n) {
        if(sz(g[i]) == 1) {
            ref[i] = x;
            bfs.push(i);
            x++;
        }
    }
    ref[k] = -1;
    bfs.push(k);
    while(!bfs.empty()) {
        ll i = bfs.front();
        bfs.pop();
        FOR(j, sz(g[i])) {
            ll k = g[i][j];
            if(!ref[k]) {
                ref[k] = ref[i];
                bfs.push(k);
            } else if(ref[i] == -1 && ref[k] != -1) {
                rv.insert(ref[k]);
            }
        }
    }
    cout << sz(rv) << '\n';
    return 0;
}