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
    ll q;
    cin >> q;
    map<ll, bool> s;
    map<ll, ll> curr;
    map<ll, set<ll>> factors, multiples;
    while (q--) {
        char c;
        cin >> c;
        // + x: add x to the set
        // - x: remove x from the set
        // ? k: print the smallest multiple of k that is not in the set
        if (c == '+') {
            ll x;
            cin >> x;
            s[x] = true;
            FORE (y, factors[x]) {
                multiples[y].erase(x);
            }
        } elif (c == '-') {
            ll x;
            cin >> x;
            s[x] = false;
            FORE (y, factors[x]) {
                multiples[y].insert(x);
            }
        } else {
            ll k;
            cin >> k;
            if (multiples[k].empty()) {
                ll x = max(k, curr[k]);
                while (s[x]) {
                    factors[x].insert(k);
                    x += k;
                }
                curr[k] = x;
                cout << x << '\n';
            } else {
                cout << *multiples[k].begin() << '\n';
            }
        }
    }
    return 0;
}