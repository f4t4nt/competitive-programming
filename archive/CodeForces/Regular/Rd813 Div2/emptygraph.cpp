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

// https://codeforces.com/contest/1712/problem/D

int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll n, k;
        cin >> n >> k;
        vector<ll> a(n);
        vector<pair<ll, ll>> b(n);
        FOR(i, n) {
            cin >> a[i];
            b[i] = mp(a[i], i);
        }
        ssort(b);
        FOR(i, k - 1) {
            a[b[i].second] = 1e9;
        }
        ll rv = 0;
        FOR(i, n - 1) {
            vector<ll> v(4);
            v[0] = a[i];
            v[1] = a[i + 1];
            ll j = k - 1;
            while (j < n && (b[j].second == i || b[j].second == i + 1)) {
                j++;
            }
            if (j < n) {
                v[2] = 2 * a[b[j].second];
                j++;
                while (j < n && (b[j].second == i || b[j].second == i + 1)) {
                    j++;
                }
                if (j < n) {
                    v[3] = 2 * a[b[j].second];
                } else {
                    v[3] = 1e9;
                }
            } else {
                v[2] = 1e9;
                v[3] = 1e9;
            }
            ssort(v);
            rv = max(rv, v[1]);
        }
        cout << rv << '\n';
    }
    return 0;
}