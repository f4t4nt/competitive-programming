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
        ll n, k, l;
        cin >> n >> k;
        vector<ll> a(n), b;
        FOR(i, n) {
            cin >> a[i];
        }
        if (k == 1) {
            l = 0;
        }
        b.pb(a[0]);
        FOB(i, 1, n) {
            if ((a[i] >= 0) == (a[i - 1] >= 0)) {
                b.back() += a[i];
            } else {
                b.pb(a[i]);
            }
            if (i == k - 1) {
                l = sz(b) - 1;
            }
        }
        vector<ll> dp(sz(b), -1e18);
        dp[l] = b[l];
        ll i = l, j = l, timer = 6;
        pair<ll, ll> ref = mp(l, l);
        bool left = true;
        while (i > 0 && j < sz(b) - 1) {
            if (left) {
                ll m = dp[i];
                while (i > 0 && dp[i] >= 0 && dp[i] + b[i - 1] >= 0) {
                    i--;
                    dp[i] = dp[i + 1] + b[i];
                    if (dp[i] > m) {
                        timer = 6;
                        m = dp[i];
                        ref.first = i;
                    }
                }
                dp[ref.second] = m;
                j = ref.second;
            } else {
                ll m = dp[j];
                while (j < sz(b) - 1 && dp[j] >= 0 && dp[j] + b[j + 1] >= 0) {
                    j++;
                    dp[j] = dp[j - 1] + b[j];
                    if (dp[j] > m) {
                        timer = 6;
                        m = dp[j];
                        ref.second = j;
                    }
                }
                dp[ref.first] = m;
                i = ref.first;
            }
            timer--;
            if (timer == 0) {
                break;
            }
            left = !left;
        }
        if ((i <= 0 && dp[0] >= 0) ||
            (j >= sz(b) - 1 && dp[sz(b) - 1] >= 0)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}