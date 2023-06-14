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
    ll n, k;
    cin >> n >> k;
    vector<set<pair<ll, ll>>> coords(k);
    vector<vector<ll>> rows(k, vector<ll>(n, 1e18)), cols(k, vector<ll>(n, 1e18));
    FOR (i, n) {
        FOR (j, n) {
            ll x;
            cin >> x;
            coords[x - 1].insert({i, j});
            if (x == 1) {
                rows[x - 1][i] = 0;
                cols[x - 1][j] = 0;
            }
        }
    }
    bool valid = true;
    FOR (i, k) {
        if (sz(coords[i]) == 0) {
            valid = false;
            break;
        }
    }
    if (!valid) {
        cout << -1 << '\n';
        return 0;
    }
    FOB (x, 1, k) {
        FORE (coord, coords[x]) {
            ll dist = 0, min_dist = 1e18;
            bool tmp = true;
            while (tmp) {
                tmp = false;
                if (coord.first + dist < n) {
                    min_dist = min(rows[x - 1][coord.first + dist] + dist * dist, min_dist);
                    tmp = true;
                }
                if (coord.first - dist >= 0) {
                    min_dist = min(min_dist, rows[x - 1][coord.first - dist] + dist * dist);
                    tmp = true;
                }
                if (coord.second + dist < n) {
                    min_dist = min(min_dist, cols[x - 1][coord.second + dist] + dist * dist);
                    tmp = true;
                }
                if (coord.second - dist >= 0) {
                    min_dist = min(min_dist, cols[x - 1][coord.second - dist] + dist * dist);
                    tmp = true;
                }
                dist++;
            }
            rows[x][coord.first] = min(rows[x][coord.first], min_dist);
            cols[x][coord.second] = min(cols[x][coord.second], min_dist);
        }
    }
    ll rv = 1e18;
    FOR (i, n) {
        rv = min(rv, rows[k - 1][i]);
    }
    FOR (i, n) {
        rv = min(rv, cols[k - 1][i]);
    }
    cout << rv << '\n';
    return 0;
}