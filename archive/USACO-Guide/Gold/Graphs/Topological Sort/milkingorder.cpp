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

bool get_ordering(ll &n, ll &mid, vector<vector<ll>> &observations) {
    vector<vector<ll>> adj(n);
    FOR (i, mid) {
        ll v = observations[i][0];
        FOB (j, 1, sz(observations[i])) {
            ll u = observations[i][j];
            adj[v - 1].pb(u - 1);
            v = u;
        }
    }
    vector<ll> in(n);
    FORE (v, adj) {
        FORE (u, v) {
            in[u]++;
        }
    }
    queue<ll> q;
    FOR (i, n) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    vector<ll> top_sort;
    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        top_sort.pb(v);
        FORE (u, adj[v]) {
            in[u]--;
            if (in[u] == 0) {
                q.push(u);
            }
        }
    }
    if (sz(top_sort) != n) {
        return false;
    } else {
        return true;
    }
}

int main() {
    ifstream cin("milkorder.in");
    ofstream cout("milkorder.out");

    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> observations(m);
    FOR (i, m) {
        ll k;
        cin >> k;
        observations[i].resize(k);
        FOR (j, k) {
            cin >> observations[i][j];
        }
    }
    ll lo = 0, hi = m;
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;
        if (get_ordering(n, mid, observations)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    vector<vector<ll>> adj(n);
    FOR (i, lo) {
        ll v = observations[i][0];
        FOB (j, 1, sz(observations[i])) {
            ll u = observations[i][j];
            adj[v - 1].pb(u - 1);
            v = u;
        }
    }
    vector<ll> in(n);
    FORE (v, adj) {
        FORE (u, v) {
            in[u]++;
        }
    }
    priority_queue<ll, vector<ll>, greater<ll>> q;
    FOR (i, n) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    vector<ll> top_sort;
    while (!q.empty()) {
        ll v = q.top();
        q.pop();
        top_sort.pb(v);
        FORE (u, adj[v]) {
            in[u]--;
            if (in[u] == 0) {
                q.push(u);
            }
        }
    }
    FOR (i, n - 1) {
        cout << top_sort[i] + 1 << " ";
    }
    cout << top_sort[n - 1] + 1 << '\n';
    return 0;
}