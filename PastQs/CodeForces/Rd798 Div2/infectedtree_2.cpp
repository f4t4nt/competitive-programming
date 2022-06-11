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

int main() {
    ll t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        vector<vector<ll>> e(n);
        FOR(i, n - 1) {
            ll a, b;
            cin >> a >> b;
            e[a - 1].pb(b - 1);
            e[b - 1].pb(a - 1);
        }
        vector<pair<ll, vector<ll>>> t(n);
        queue<ll> bfs;
        vector<ll> v(n, 0);
        bfs.push(0);
        v[0] = true;
        while(sz(bfs)) {
            ll x = bfs.front();
            bfs.pop();
            FOR(i, sz(e[x])) {
                ll y = e[x][i];
                if(!v[y]) {
                    v[y]++;
                    bfs.push(y);
                    t[x].second.pb(y);
                    t[y].first = x;
                }
            }
        }
        vector<ll> ref(n, 1);
        v = vector<ll>(n, 0);
        FOR(i, n) {
            v[i] = sz(t[i].second);
            if(!v[i]) bfs.push(i);
        }
        while(sz(bfs)) {
            ll x = bfs.front();
            bfs.pop();
            ref[t[x].first] += ref[x];
            v[t[x].first]--;
            if(!v[t[x].first]) bfs.push(t[x].first);
        }
        vector<ll> dp(n);
        v = vector<ll>(n, 0);
        FOR(i, n) {
            v[i] = sz(t[i].second);
            if(!v[i]) bfs.push(i);
        }
        while(sz(bfs)) {
            ll x = bfs.front();
            bfs.pop();
            if(sz(t[x].second) == 2) {
                dp[x] = max(
                    dp[t[x].second[0]] + ref[t[x].second[1]] - 1,
                    dp[t[x].second[1]] + ref[t[x].second[0]] - 1);
            } elif(sz(t[x].second) == 1) {
                dp[x] = ref[t[x].second[0]] - 1;
            }
            v[t[x].first]--;
            if(x && !v[t[x].first]) bfs.push(t[x].first);
        }
        cout << dp[0] << '\n';
    }
    return 0;
}