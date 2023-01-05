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
        ll n, rv = 0;
        cin >> n;
        vector<ll> a(n), zeros;
        FOR (i, n) {
            cin >> a[i];
            if (a[i] == 0) {
                zeros.pb(i);
            }
        }
        zeros.pb(n);
        ll s= 0;
        FOR (i, zeros[0]) {
            s += a[i];
            if (s == 0) {
                rv++;
            }
        }
        FOR (z_i, sz(zeros) - 1) {
            ll z = zeros[z_i], nz = zeros[z_i + 1];
            ll s = 0;
            map<ll, ll> ref;
            ref[0] = 1;
            FOR (i, nz - z - 1) {
                s += a[z + i + 1];
                ref[s]++;
            }
            ll mc = 0;
            FORE (p, ref) {
                mc = max(mc, p.second);
            }
            rv += mc;
        }
        cout << rv << '\n';
    }
    return 0;
}