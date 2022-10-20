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

bool possible(vector<ll> a, ll &k) {
    multiset<ll> a_set;
    FORE(x, a) {
        a_set.insert(x);
    }
    FOB(i, 1, k + 1) {
        ll x = k - i + 1;
        auto it = a_set.upper_bound(x);
        if (it == a_set.begin()) {
            return false;
        }
        it--;
        a_set.erase(it);
        if (a_set.empty()) {
            return true;
        }
        it = a_set.upper_bound(1);
        if (it != a_set.begin()) {
            it--;
        }
        ll y = *it;
        a_set.erase(it);
        a_set.insert(x + y);
    }
    return true;
}

int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> a(n);
        FOR(i, n) cin >> a[i];
        ll lo = 0, hi = n;
        while (lo < hi) {
            ll mid = (lo + hi + 1) / 2;
            if (possible(a, mid)) lo = mid;
            else hi = mid - 1;
        }
        cout << lo << '\n';
    }
    return 0;
}