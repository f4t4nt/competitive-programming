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

int main() {
    ll n1, n2, m1, m2;
    cin >> n1 >> n2 >> m1 >> m2;
    vector<pair<ll, ll>> edges1(m1), edges2(m2);
    FOR(i, m1) {
        cin >> edges1[i].first >> edges1[i].second;
        edges1[i].first--; edges1[i].second--;
    }
    FOR(i, m2) {
        cin >> edges2[i].first >> edges2[i].second;
        edges2[i].first--; edges2[i].second--;
    }
    vector<vector<ll>> adj1(n1), adj2(n2);
    vector<ll> deg1(n1), deg2(n2);
    FORE(e, edges1) {
        adj1[e.first].pb(e.second);
        deg1[e.second]++;
    }
    FORE(e, edges2) {
        adj2[e.first].pb(e.second);
        deg2[e.second]++;
    }
    queue<ll> q1, q2;
    FOR(i, n1) if (deg1[i] == 0) q1.push(i);
    FOR(i, n2) if (deg2[i] == 0) q2.push(i);
    vector<ll> top_sort1, top_sort2;
    while (!q1.empty()) {
        ll v = q1.front(); q1.pop();
        top_sort1.pb(v);
        FORE(u, adj1[v]) {
            deg1[u]--;
            if (deg1[u] == 0) q1.push(u);
        }
    }
    while (!q2.empty()) {
        ll v = q2.front(); q2.pop();
        top_sort2.pb(v);
        FORE(u, adj2[v]) {
            deg2[u]--;
            if (deg2[u] == 0) q2.push(u);
        }
    }
    vector<set<ll>> dp1(n1), dp2(n2);
    dp1[0].insert(0);
    dp2[0].insert(0);
    FORE(v, top_sort1) {
        FORE(u, adj1[v]) {
            FORE(l, dp1[v]) {
                dp1[u].insert(l + 1);
            }
        }
    }
    FORE(v, top_sort2) {
        FORE(u, adj2[v]) {
            FORE(l, dp2[v]) {
                dp2[u].insert(l + 1);
            }
        }
    }
    set<ll> sums;
    FORE(v, dp1[n1 - 1]) {
        FORE(u, dp2[n2 - 1]) {
            sums.insert(v + u);
        }
    }
    ll q;
    cin >> q;
    while(q--) {
        ll s;
        cin >> s;
        if (sums.count(s)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}