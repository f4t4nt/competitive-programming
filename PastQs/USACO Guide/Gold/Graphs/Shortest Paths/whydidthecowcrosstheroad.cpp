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
    ifstream cin("visitfj.in");
    ofstream cout("visitfj.out");

    ll n, t;
    cin >> n >> t;
    vector<vector<pair<ll, ll>>> adj(n * n);
    ll dx[] = {-3, -2, -2, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 2, 2, 3};
    ll dy[] = {0, -1, 1, -2, 0, 2, -3, -1, 1, 3, -2, 0, 2, -1, 1, 0};
    vector<ll> weights(n * n);
    FOR (i, n) {
        FOR (j, n) {
            cin >> weights[i * n + j];
        }
    }
    FOR (i, n) {
        FOR (j, n) {
            FOR (k, 16) {
                ll x = i + dx[k];
                ll y = j + dy[k];
                if (x >= 0 && x < n && y >= 0 && y < n) {
                    adj[i * n + j].pb({x * n + y, 3 * t + weights[x * n + y]});
                }
            }
        }
    }
    adj[(n - 1) * n + n - 3].pb({n * n - 1, 2 * t});
    adj[(n - 1) * n + n - 2].pb({n * n - 1, t});
    adj[(n - 2) * n + n - 1].pb({n * n - 1, t});
    adj[(n - 2) * n + n - 2].pb({n * n - 1, 2 * t});
    adj[(n - 3) * n + n - 1].pb({n * n - 1, 2 * t});
    vector<ll> dist(n * n, 1e18);
    dist[0] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        ll d = pq.top().first;
        ll u = pq.top().second;
        pq.pop();
        if (d > dist[u]) {
            continue;
        }
        for (auto v : adj[u]) {
            if (dist[u] + v.second < dist[v.first]) {
                dist[v.first] = dist[u] + v.second;
                pq.push({dist[v.first], v.first});
            }
        }
    }
    cout << dist[n * n - 1] << '\n';
    return 0;
}