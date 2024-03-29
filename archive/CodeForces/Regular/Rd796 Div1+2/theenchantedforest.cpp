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

// https://codeforces.com/contest/1688/problem/D

int main() {
    ll t;
    cin >> t;
    while(t--) {
        ll n, k, s = 0;
        cin >> n >> k;
        vector<ll> a(n);
        FOR(i, n) {
            cin >> a[i];
            if(i < k) s += a[i];
        }
        ll max_s = s;
        FOB(i, k, n) {
            s += a[i] - a[i - k];
            max_s = max(max_s, s);
        }
        if(n > k) max_s += k * (k - 1) / 2;
        else {
            ll m = k - n;
            max_s += n * m + n * (n - 1) / 2;
            // if there are n points and k > n time,
            // we will spend (k - n) time at one
            // end and travel to the other end in
            // (n - 1) time. during this tme, the
            // mushrooms will have grown by (k - n)
            // for n positions.
        }
        cout << max_s << '\n';
    }
    return 0;
}