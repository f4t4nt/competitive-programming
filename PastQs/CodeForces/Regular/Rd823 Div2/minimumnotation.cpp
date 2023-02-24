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
        str s;
        cin >> s;
        ll n = sz(s);
        vector<ll> a(n), b, ref(10, -1), cnt0(10), cnt1(10);
        FOR(i, n) {
            a[i] = s[i] - '0';
            ref[a[i]] = i;
        }
        ll i = 0, tmp = 10;
        FOR(j, 10) {
            while (i <= ref[j]) {
                if (a[i] == j) {
                    cnt0[j]++;
                } else {
                    cnt1[a[i]]++;
                    tmp = min(tmp, a[i] + 1);
                }
                i++;
            }
        }
        FOR(j, 11) {
            if (j < 10) {
                while (cnt0[j]--) {
                    b.pb(j);
                }
            }
            if (j > 0) {
                while (cnt1[j - 1]--) {
                    b.pb(min(j, 9LL));
                }
            }
        }
        FOR(i, n) {
            cout << b[i];
        }
        cout << '\n';
    }
    return 0;
}