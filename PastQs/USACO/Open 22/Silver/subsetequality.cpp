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

// http://usaco.org/index.php?page=viewproblem2&cpid=1231

const ll MAX_CHAR = 18;

str filter(str s, ll i, ll j) {
    str rv;
    FORE(c, s) {
        if(c - 'a' == i || c - 'a' == j) {
            rv += c;
        }
    }
    return rv;
}

int main() {
    str s1, s2;
    cin >> s1 >> s2;
    vector<bool> dp(1 << MAX_CHAR, true);
    vector<ll> cnt1(MAX_CHAR), cnt2(MAX_CHAR);
    FOR(i, s1.size()) {
        cnt1[s1[i] - 'a']++;
    }
    FOR(i, s2.size()) {
        cnt2[s2[i] - 'a']++;
    }
    FOR(i, MAX_CHAR) {
        if (cnt1[i] != cnt2[i]) {
            dp[1 << i] = false;
        }
    }
    FOR(i, MAX_CHAR) {
        FOB(j, i, MAX_CHAR) {
            if(!dp[1 << i] ||
                !dp[1 << j] ||
                filter(s1, i, j) != filter(s2, i, j)) {
                dp[1 << i | 1 << j] = false;
            }
        }
    }
    FOR(x, 1 << MAX_CHAR) {
        if(!dp[x]) {
            FOR(i, MAX_CHAR) {
                dp[x | 1 << i] = false;
            }
        }
    }
    ll t;
    cin >> t;
    FOR(i, t) {
        str s;
        cin >> s;
        ll x = 0;
        FORE(c, s) {
            x |= 1 << (c - 'a');
        }
        if(dp[x]) {
            cout << "Y";
        } else {
            cout << "N";
        }
    }
    cout << '\n';
    return 0;
}