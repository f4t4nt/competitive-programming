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
        ll n, m, rv = 0;
        cin >> n >> m;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
        }
        ll presum = 0;
        multiset<ll> pre;
        for (ll i = m - 1; i > 0; i--) {
            presum += a[i];
            if (a[i] > 0) {
                pre.insert(a[i]);
            }
            while (presum > 0) {
                auto it = pre.rbegin();
                presum -= *it * 2;
                pre.erase(--it.base());
                rv++;
            }
        }
        ll postsum = 0;
        multiset<ll> post;
        for (ll i = m; i < n; i++) {
            postsum += a[i];
            if (a[i] < 0) {
                post.insert(a[i]);
            }
            while (postsum < 0) {
                auto it = post.begin();
                postsum -= *it * 2;
                post.erase(it);
                rv++;
            }
        }
        cout << rv << '\n';
    }
    return 0;
}