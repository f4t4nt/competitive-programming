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
        ll n, nonzeros = 0;
        cin >> n;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
            if (a[i] != 0) {
                nonzeros++;
            }
        }
        if (nonzeros % 2) {
            cout << -1 << '\n';
        } else {
            vector<pair<ll, ll>> rv;
            ll i = 0, sum = 0;
            while (i < n) {
                ll j = i;
                while (j < n && a[j] == 0) {
                    j++;
                }
                if (j > i) {
                    rv.pb(mp(i + 1, j));
                }
                i = j;
                if (i == n) {
                    break;
                }
                ll k = i + 1;
                while (k < n && a[k] == 0) {
                    k++;
                }
                if (k == n) {
                    rv.pb(mp(i + 1, n));
                } elif (a[i] == -a[k]) {
                    rv.pb(mp(i + 1, k));
                    rv.pb(mp(k + 1, k + 1));
                } elif (i < k - 1) {
                    rv.pb(mp(i + 1, k - 1));
                    rv.pb(mp(k, k + 1));
                } else {
                    rv.pb(mp(i + 1, k + 1));
                }
                i = k + 1;
            }
            cout << sz(rv) << '\n';
            FORE (p, rv) {
                cout << p.first << ' ' << p.second << '\n';
            }
        }
    }
    return 0;
}