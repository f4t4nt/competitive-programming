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
        ll n, m;
        cin >> n >> m;
        vector<pair<ll, ll>> pos(m);
        vector<ll> x(n), y(n);
        FOR(i, m) {
            cin >> pos[i].first >> pos[i].second;
            x[pos[i].first - 1]++;
            y[pos[i].second - 1]++;
        }
        bool valid = true;
        FOR(i, n) {
            if (x[i] > 2 || y[i] > 2) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            cout << "NO\n";
            continue;
        }
        bool two = false;
        FOR(i, n) {
            if (x[i] == 2 || y[i] == 2) {
                two = true;
                break;
            }
        }
        if (two && m > n) {
            cout << "NO\n";
            continue;
        }
        bool allOnes = true;
        FOR(i, n) {
            if (x[i] != 1 || y[i] != 1) {
                allOnes = false;
                break;
            }
        }
        if (allOnes && m >= n) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
    return 0;
}