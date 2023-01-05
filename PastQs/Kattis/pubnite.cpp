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

int main () {
    cout << fixed << setprecision(9);

    ld x_s, y_s, s_s, r_i, r_f, x_a, y_a, s_a, r_a;
    cin >> x_s >> y_s >> s_s >> r_i >> r_f >> x_a >> y_a >> s_a;
    r_a = sqrt((x_a - x_s) * (x_a - x_s) + (y_a - y_s) * (y_a - y_s));
    if(r_a <= r_f || (r_a <= r_i && s_a >= s_s)) {
        cout << 0.0;
    } elif (r_a < r_i){
        ld t0 = (r_i - r_a) / (ld) (s_s - s_a), t1 = (r_a - r_f) / (ld) s_a;
        if (t1 < t0) {
            cout << t1;
        } else {
            cout << t1 - t0;
        }
    } elif (s_a <= s_s){
        cout << (r_a - r_f) / (ld) s_a;
    } else {
        ld t0 = (r_a - r_i) / (ld) (s_a - s_s), t1 = (r_a - r_f) / (ld) s_a;
        if (t1 <= t0) {
            cout << t1;
        } else {
            cout << t0;
        }
    }
    return 0;
}