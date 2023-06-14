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

// https://codeforces.com/contest/1712/problem/C

int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        set<ll> ref;
        vector<ll> a(n);
        FOR(i, n) cin >> a[i];
        set<ll> rv;
        while (true) {
            ll i = n - 1;
            while (i > 0 && a[i - 1] <= a[i]) i--;
            if (i == 0) break;
            ll j = i - 1;
            while (j >= 0) {
                if (a[j]) {
                    rv.insert(a[j]);
                }
                a[j] = 0;
                j--;
            }
            while (i < n) {
                if (rv.find(a[i]) != rv.end()) {
                    a[i] = 0;
                }
                i++;
            }
        }
        cout << sz(rv) << endl;
    }
    return 0;
}