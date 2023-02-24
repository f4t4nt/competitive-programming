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

bool is_simple_polygon(vector<pair<ld, ld>> coords, vector<ll> ordering) {
    FOR (i, 7) {
        FOR (j, 7) {
            if (i == j) {
                continue;
            }
            ld x1 = coords[ordering[i]].first;
            ld y1 = coords[ordering[i]].second;
            ld x2 = coords[ordering[(i + 1) % 7]].first;
            ld y2 = coords[ordering[(i + 1) % 7]].second;
            ld x3 = coords[ordering[j]].first;
            ld y3 = coords[ordering[j]].second;
            ld x4 = coords[ordering[(j + 1) % 7]].first;
            ld y4 = coords[ordering[(j + 1) % 7]].second;
            ld denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
            if (denom == 0) {
                continue;
            }
            ld t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denom;
            ld u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denom;
            if (t > 0 && t < 1 && u > 0 && u < 1) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ll n;
    cin >> n;
    while (n--) {
        vector<pair<ld, ld>> alice(7);
        FOR (i, 7) {
            cin >> alice[i].first >> alice[i].second;
        }
        ld bob;
        cin >> bob;
        bob = pow(bob, 1.0 / 3.0) * 4;
        pair<ld, set<vector<ll>>> orderings = {1e9, {}};
        vector<ll> ordering(7);
        iota(ordering.begin(), ordering.end(), 0);
        do {
            if (!is_simple_polygon(alice, ordering)) {
                continue;
            }
            ld area = 0;
            FOR (i, 7) {
                area += (alice[ordering[i]].first * alice[ordering[(i + 1) % 7]].second - alice[ordering[(i + 1) % 7]].first * alice[ordering[i]].second);
            }
            area = abs(area) / 2;
            if (abs(area - bob) < orderings.first) {
                orderings = {abs(area - bob), {ordering}};
            } elif (abs(area - bob) == orderings.first) {
                orderings.second.insert(ordering);
            }
        } while (next_permutation(ordering.begin() + 1, ordering.end()));
        set<vector<ll>> best_orderings;
        FORE (ordering, orderings.second) {
            vector<ll> ordering_copy = ordering;
            FOR (i, 7) {
                best_orderings.insert(ordering_copy);
                rotate(ordering_copy.begin(), ordering_copy.begin() + 1, ordering_copy.end());
            }
            vector<ll> reflected_ordering = ordering;
            flip(reflected_ordering);
            FOR (i, 7) {
                best_orderings.insert(reflected_ordering);
                rotate(reflected_ordering.begin(), reflected_ordering.begin() + 1, reflected_ordering.end());
            }
        }
        FORE (i, *best_orderings.begin()) {
            cout << i + 1 << ' ';
        }
        cout << '\n';
    }
    return 0;
}