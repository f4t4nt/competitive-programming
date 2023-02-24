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
    while (t--) {
        ll n;
        cin >> n;
        ld lo = 1e8, hi = 0;
        vector<ld> x(n), t(n);
        FOR(i, n) {
            cin >> x[i];
            lo = min(lo, x[i]);
            hi = max(hi, x[i]);
        }
        FOR(i, n) {
            cin >> t[i];
        }
        while (hi - lo > 1e-7) {
            ld mid1 = lo + (hi - lo) / 3;
            ld mid2 = hi - (hi - lo) / 3;
            ld t1 = 0, t2 = 0;
            FOR(i, n) {
                t1 = max(t1, t[i] + abs(x[i] - mid1));
                t2 = max(t2, t[i] + abs(x[i] - mid2));
            }
            if (t1 < t2) {
                hi = mid2;
            } else {
                lo = mid1;
            }
        }
        cout << fixed << setprecision(10) << lo << '\n';
    }
    return 0;
}