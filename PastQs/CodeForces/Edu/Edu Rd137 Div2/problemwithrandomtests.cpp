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

bool bin_or_geq(vector<bool> &s, vector<bool> &r, ll &i) {
    bool geq = false;
    vector<bool> rv(sz(s), false);
    FOR (j, sz(s)) {
        if (s[j] || (j - i >= 0 && s[j - i])) {
            rv[j] = true;
        }
        if (!rv[j] && r[j] && !geq) {
            return false;
        } elif (rv[j] && !r[j] && !geq) {
            geq = true;
        }
    }
    r = rv;
    return true;
}

int main() {
    ll n, cnt = 1e3;
    cin >> n;
    vector<bool> s(n);
    FOR (i, n) {
        char c;
        cin >> c;
        s[i] = c == '1';
    }
    vector<bool> rv = s;
    ll i = 0;
    while (i < n && cnt > 0) {
        if (!bin_or_geq(s, rv, i)) {
            cnt--;
        }
        i++;
    }
    ll j = 0;
    while (j < sz(rv) - 1 && !rv[j]) {
        j++;
    }
    FOR (k, sz(rv) - j) {
        if (rv[j + k]) {
            cout << '1';
        } else {
            cout << '0';
        }
    }
    cout << '\n';
    return 0;
}