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

// http://usaco.org/index.php?page=viewproblem2&cpid=1232

int main() {
    str s;
    cin >> s;
    ll n = sz(s);
    vector<vector<ll>> ref(n + 1, vector<ll>(3, 0));
    FOR(i, n) {
        ref[i + 1] = ref[i];
        if(s[i] == 'C') {
            ref[i + 1][0]++;
        } elif(s[i] == 'O') {
            ref[i + 1][1]++;
        } elif(s[i] == 'W') {
            ref[i + 1][2]++;
        }
    }
    ll t;
    cin >> t;
    FOR(i, t) {
        ll l, r;
        cin >> l >> r;
        ll c = ref[r][0] - ref[l - 1][0],
            o = ref[r][1] - ref[l - 1][1],
            w = ref[r][2] - ref[l - 1][2];
        if((o + w) % 2 == 0 && (c + o) % 2 == 1) {
            cout << "Y";
        } else {
            cout << "N";
        }
    }
    cout << '\n';
    return 0;
}