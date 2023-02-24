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

ld helper(ld x, ll n, vector<pair<ld, ld>> coords) {
    ld rv = 0;
    FOR (i, n) {
        rv = max(rv, (coords[i].first - x) * (coords[i].first - x) +
            coords[i].second * coords[i].second);
    }
    return rv;
}

int main() {
    while (true) {
        str n_str;
        getline(cin, n_str);
        ll n = stoll(n_str);
        if (n == 0) {
            break;
        }
        vector<pair<ld, ld>> coords(n);
        FOR (i, n) {
            str coord_str;
            getline(cin, coord_str);
            istringstream coord_stream(coord_str);
            ld x, y;
            coord_stream >> x >> y;
            coords[i] = mp(x, y);
        }
        getline(cin, n_str);
        ld l = -2e5, r = 2e5, t = 1e18;
        while (r - l > 1e-9) {
            ld m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
            ld v1 = helper(m1, n, coords), v2 = helper(m2, n, coords);
            t = min(t, min(v1, v2));
            if (v1 < v2) {
                r = m2;
            } else {
                l = m1;
            }
        }
        cout << fixed << setprecision(10) << l << ' ' << sqrt(t) << '\n';
    }
    return 0;
}