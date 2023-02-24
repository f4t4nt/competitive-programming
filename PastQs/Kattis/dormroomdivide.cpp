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

ld shoelace(vector<pair<ld, ld>> &coords) {
    ld area = 0;
    FOR(i, sz(coords)) {
        area += (coords[i].first * coords[(i + 1) % sz(coords)].second - coords[(i + 1) % sz(coords)].first * coords[i].second);
    }
    return abs(area) / 2;
}

ld triangle_area(pair<ld, ld> &a, pair<ld, ld> &b, pair<ld, ld> &c) {
    return abs((a.first * (b.second - c.second) + b.first * (c.second - a.second) + c.first * (a.second - b.second)) / 2);
}

int main() {
    ll n;
    cin >> n;
    vector<pair<ld, ld>> coords(n);
    FORE(coord, coords) {
        cin >> coord.first >> coord.second;
    }
    ld total_area = shoelace(coords), target_area = total_area / 2;
    ld curr_area = 0, prev_area = 0;
    ll i = 0;
    while (curr_area < target_area) {
        prev_area = curr_area;
        curr_area += triangle_area(coords[0], coords[i], coords[(i + 1) % n]);
        i++;
    }
    if (curr_area == target_area) {
        cout << fixed << setprecision(10) << coords[i].first <<  ' ' << coords[i].second << endl;
    } else {
        ld ratio = (target_area - prev_area) / (curr_area - prev_area);
        ld x = coords[i - 1].first + ratio * (coords[i].first - coords[i - 1].first);
        ld y = coords[i - 1].second + ratio * (coords[i].second - coords[i - 1].second);
        cout << fixed << setprecision(10) << x <<  ' ' << y << endl;
    }
    return 0;
}