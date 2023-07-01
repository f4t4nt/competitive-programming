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
    ll n;
    cin >> n;
    vector<ll> k(n);
    FOR (i, n) {
        cin >> k[i];
    }
    vector<pair<ll, ll>> dim(n);
    stack<pair<ll, ll>> left, right;
    FOR (i, n) {
        while (sz(left) && left.top().first >= k[i]) {
            left.pop();
        }
        if (sz(left)) {
            dim[i].first = left.top().second;
        } else {
            dim[i].first = -1;
        }
        left.push({k[i], i});
    }
    FORR (i, n) {
        while (sz(right) && right.top().first >= k[i]) {
            right.pop();
        }
        if (sz(right)) {
            dim[i].second = right.top().second;
        } else {
            dim[i].second = n;
        }
        right.push({k[i], i});
    }
    ll rv = 0;
    FOR (i, n) {
        rv = max(rv, k[i] * (dim[i].second - dim[i].first - 1));
    }
    cout << rv << '\n';
    return 0;
}