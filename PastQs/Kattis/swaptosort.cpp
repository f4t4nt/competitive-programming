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

// https://open.kattis.com/problems/swaptosort

struct DSU {
	vector<ll> e;
    DSU(ll n) : e(n, -1) {}
    bool same_set(ll a, ll b) { return find(a) == find(b); }
    ll size(ll x) { return -e[find(x)]; }
    ll find(ll x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool unite(ll x, ll y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y]; e[y] = x;
        return true;
    }
};

int main() {
    ll n, k;
    cin >> n >> k;
    vector<pair<ll, ll>> a(k);
    FOR (i, k) {
        cin >> a[i].first >> a[i].second;
        a[i].first--; a[i].second--;
    }
    DSU dsu(n);
    FOR (i, k) {
        dsu.unite(a[i].first, a[i].second);
    }
    bool valid = true;
    FOR (i, n) {
        if (!dsu.same_set(i, n - i - 1)) {
            valid = false;
            break;
        }
    }
    if (valid) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return 0;
}