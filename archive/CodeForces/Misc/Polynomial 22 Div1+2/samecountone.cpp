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
    ll t;
    cin >> t;
    while (t--) {
        ll n, m, s = 0;
        cin >> n >> m;
        vector<vector<ll>> a(n, vector<ll>(m));
        vector<ll> b(n);
        FOR (i, n) {
            FOR (j, m) {
                cin >> a[i][j];
                if (a[i][j] == 1) {
                    b[i]++;
                }
            }
            s += b[i];
        }
        if (s % n != 0) {
            cout << "-1\n";
            continue;
        }
        s /= n;
        vector<tuple<ll, ll, ll>> rv;
        FOR (j, m) {
            vector<ll> less, more;
            FOR (i, n) {
                if (b[i] < s && a[i][j] == 0) {
                    less.pb(i);
                } elif (b[i] > s && a[i][j] == 1) {
                    more.pb(i);
                }
            }
            ll i = 0;
            while (i < sz(less) && i < sz(more)) {
                a[less[i]][j] = 1;
                a[more[i]][j] = 0;
                b[less[i]]++;
                b[more[i]]--;
                rv.pb({more[i] + 1, less[i] + 1, j + 1});
                i++;
            }
        }
        cout << sz(rv) << '\n';
        FORE (x, rv) {
            cout << get<0>(x) << ' ' << get<1>(x) << ' ' << get<2>(x) << '\n';
        }
    }
    return 0;
}