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

bool helper(vector<ll> &cnt, ll distinct) {
    FOR (j, 10) {
        if (cnt[j] > distinct) {
            return false;
        }
    }
    return true;
}

int main() {
    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        str s;
        cin >> s;
        ll rv = n;
        FOB (i, 1, n) {
            if (s[i] != s[i - 1]) {
                rv++;
            }
        }
        FOB (i, 2, n) {
            if (!(s[i] == s[i - 1] && s[i] == s[i - 2])) {
                rv++;
            }
        }
        FOB (len, 4, min(n + 1, 101LL)) {
            ll distinct = 0;
            vector<ll> cnt(10);
            FOR (i, len) {
                cnt[s[i] - '0']++;
                if (cnt[s[i] - '0'] == 1) {
                    distinct++;
                }
            }
            if (helper(cnt, distinct)) {
                rv++;
            }
            FOB (i, len, n) {
                cnt[s[i - len] - '0']--;
                if (cnt[s[i - len] - '0'] == 0) {
                    distinct--;
                }
                cnt[s[i] - '0']++;
                if (cnt[s[i] - '0'] == 1) {
                    distinct++;
                }
                if (helper(cnt, distinct)) {
                    rv++;
                }
            }
        }
        cout << rv << '\n';
    }
    return 0;
}