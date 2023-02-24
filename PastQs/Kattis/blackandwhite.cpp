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
    vector<ld> p(n);
    FOR (i, n) {
        cin >> p[i];
    }
    vector<ld> dp(1 << n);
    FOR (i, 1 << n) {
        vector<ll> children;
        FOR (j, n) {
            if (i & (1 << j)) {
                children.pb(j);
            }
        }
        ll count = sz(children);
        if (count <= 2) {
            continue;
        }
        vector<ld> black(count, 1), white(count, 1);
        FOR (j, count) {
            FOR (k, count) {
                if (j != k) {
                    black[j] *= 1 - p[children[k]];
                    white[j] *= p[children[k]];
                } else {
                    black[j] *= p[children[k]];
                    white[j] *= 1 - p[children[k]];
                }
            }
        }
        vector<ld> total(count);
        FOR (j, count) {
            total[j] = black[j] + white[j];
        }
        ld p_continue = 1;
        FOR (j, count) {
            p_continue -= total[j];
        }
        ld sum = 0;
        FOR (j, count) {
            sum += total[j] * dp[i - (1 << children[j])];
        }
        dp[i] = (1 + sum) / (1 - p_continue);
    }
    cout << fixed << setprecision(10) << dp[(1 << n) - 1] << endl;
    return 0;
}