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

string canReach(int c, int x1, int y1, int x2, int y2) {
    vector<bool> squares(2e3 + 1, false);
    for (int i = 0; i * i <= 2e3; i++) {
        squares[i * i] = true;
    }
    if (squares[x1 + y1] || squares[x2 + y2]) {
        return "No";
    }
    queue<pair<int, int>> q;
    q.push({x1, y1});
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (squares[x + y]) {
            continue;
        }
        if (x == x2 && y == y2) {
            return "Yes";
        }
        if (x + c <= x2 && y + c <= y2) {
            q.push({x + c, y + c});
        }
        if (x + y <= x2 && y <= y2) {
            q.push({x + y, y});
        }
        if (x <= x2 && x + y <= y2) {
            q.push({x, x + y});
        }
    }
    return "No";
}

int main() {
    ll c, x1, y1, x2, y2;
    cin >> c >> x1 >> y1 >> x2 >> y2;
    cout << canReach(c, x1, y1, x2, y2) << '\n';
    return 0;
}