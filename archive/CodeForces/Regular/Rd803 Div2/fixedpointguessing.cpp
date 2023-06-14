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
#include <uNOrdered_set>
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

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

set<ll> query(ll l, ll r) {
    cout << "? " << l << ' ' << r << endl;
    ll x = r - l + 1;
    set<ll> rv;
    FOR(i, x) {
        ll a;
        cin >> a;
        rv.insert(a);
    }
    return rv;
}

void recurse(ll &n, vector<bool> &rv, ll l, ll x) {
    if(x == 0 || count(rv.begin(), rv.end(), true) == 1) {
        return;
    }
    set<ll> q = query(l, l + x);
    FOR(i, n + 1) {
        if(i >= l && i <= l + x) {
            if(q.find(i) == q.end()) {
                rv[i] = false;
            }
        } elif(q.find(i) != q.end()) {
            rv[i] = false;
        }
    }
    ll tmp = 0;
    FOB(i, l, l + x + 1) {
        if(rv[i]) {
            tmp++;
        }
    }
    if(tmp % 2 == 0) {
        FOB(i, l, l + x + 1) {
            rv[i] = false;
        }
        recurse(n, rv, l + x + 1, x / 2);
    } else {
        FOR(i, l) {
            rv[i] = false;
        }
        FOB(i, l + x + 1, n + 1) {
            rv[i] = false;
        }
        recurse(n, rv, l, x / 2);
    }
}

int main() {
    ll t;
    cin >> t;
    while(t--) {
        ll n;
        cin >> n;
        vector<bool> rv(n + 1, true);
        rv[0] = false;
        recurse(n, rv, 1, n / 2);
        FOR(i, n + 1) {
            if(rv[i]) {
                cout << "! " << i << endl;
            }
        }
    }
    return 0;
}