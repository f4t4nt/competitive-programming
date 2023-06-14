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

// https://codeforces.com/gym/101102/problem/D

int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll n, m;
        cin >> n >> m;
        vector<vector<ll>> grid(n, vector<ll>(m));
        FOR (i, n) {
            FOR (j, m) {
                cin >> grid[i][j];
            }
        }
        ll rv = 0;
        FOR (i, n) {
            vector<pair<ll, vector<ll>>> blocks;
            FOR (j, m) {
                ll g = grid[i][j], k = i;
                while (k < n && grid[k][j] == g) {
                    k++;
                }
                if (!blocks.empty() && blocks.back().first == g) {
                    blocks.back().second.pb(k - i);
                } else {
                    blocks.pb(mp(g, vector<ll>{k - i}));
                }
            }
            FORE (block, blocks) {
                stack<pair<ll, ll>> s;
                FOR (j, sz(block.second)) {
                    while (!s.empty() && s.top().first > block.second[j]) {
                        ll h = s.top().first, w = s.top().second;
                        s.pop();
                        h -= s.empty() ? 0 : s.top().first;
                        rv += h * (j - w - 1);
                    }
                    if (!s.empty() && s.top().first == block.second[j]) {
                        continue;
                    } else {
                        s.push(mp(block.second[j], j));
                    }
                }
                while (!s.empty()) {
                    ll h = s.top().first, w = s.top().second;
                    s.pop();
                    h -= s.empty() ? 0 : s.top().first;
                    rv += h * (sz(block.second) - w - 1);
                }
            }
        }
        cout << rv << '\n';
    }
    return 0;
}