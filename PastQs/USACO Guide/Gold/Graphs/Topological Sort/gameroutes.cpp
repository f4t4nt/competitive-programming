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

constexpr ll MOD = 1e9 + 7;

int main() {
    ll n, m;
    cin >> n >> m;
    vector<pair<ll, ll>> e(m);
    FOR(i, m) {
        cin >> e[i].first >> e[i].second;
        e[i].first--;
        e[i].second--;
    }
    vector<vector<ll>> g(n);
    vector<ll> in(n);
    FORE(x, e) {
        g[x.first].pb(x.second);
        in[x.second]++;
    }
    queue<ll> q;
    FOR(i, n) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    vector<ll> top_sort;
    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        top_sort.pb(v);
        FORE(x, g[v]) {
            in[x]--;
            if (in[x] == 0) {
                q.push(x);
            }
        }
    }
    vector<ll> dp(n);
    dp[0] = 1;
    FORE(x, top_sort) {
        FORE(y, g[x]) {
            dp[y] += dp[x];
            dp[y] %= MOD;
        }
    }
    cout << dp[n - 1] << '\n';
    return 0;
}