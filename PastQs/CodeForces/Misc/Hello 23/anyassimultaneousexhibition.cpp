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

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

int main() {
    ll n;
    cin >> n;
    vector<pair<ll, ll>> out(n);
    str s = "";
    FOR (i, n) {
        s += '1';
    }
    FOR (i, n) {
        s[i] = '0';
        cout << "? " << i + 1 << ' ' << s << '\n';
        cin >> out[i].first;
        out[i].second = i;
        s[i] = '1';
    }
    s = "";
    FOR (i, n) {
        s += '0';
    }
    rsort(out);
    ll j = 0;
    s[out[j].second] = '1';
    FOB (i, 1, n) {
        cout << "? " << out[i].second + 1 << ' ' << s << '\n';
        ll ans;
        cin >> ans;
        if (ans > 0) {
            FOB (k, j + 1, i + 1) {
                s[out[k].second] = '1';
            }
            j = i;
        }
    }
    cout << "! " << s << '\n';
    return 0;
}