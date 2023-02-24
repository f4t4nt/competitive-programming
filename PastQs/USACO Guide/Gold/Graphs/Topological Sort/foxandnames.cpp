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
    ll n;
    cin >> n;
    vector<str> authors(n);
    FOR (i, n) {
        cin >> authors[i];
    }
    vector<pair<ll, ll>> edges;
    bool valid = true;
    FOB (i, 1, n) {
        ll j = 0;
        while (j < sz(authors[i]) && j < sz(authors[i - 1]) && authors[i][j] == authors[i - 1][j]) {
            j++;
        }
        if (j == sz(authors[i]) && j < sz(authors[i - 1])) {
            valid = false;
            break;
        }
        if (j < sz(authors[i]) && j < sz(authors[i - 1])) {
            edges.pb(mp(authors[i - 1][j] - 'a', authors[i][j] - 'a'));
        }
    }
    if (!valid) {
        cout << "Impossible\n";
        return 0;
    }
    vector<vector<ll>> adj(26);
    vector<ll> in(26);
    FORE (e, edges) {
        adj[e.first].pb(e.second);
        in[e.second]++;
    }
    queue<ll> q;
    FOR (i, 26) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    vector<ll> top_sort;
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        top_sort.pb(u);
        FORE (v, adj[u]) {
            in[v]--;
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }
    if (sz(top_sort) != 26) {
        cout << "Impossible\n";
    } else {
        FORE (c, top_sort) {
            cout << (char) (c + 'a');
        }
    }
    return 0;
}