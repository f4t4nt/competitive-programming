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

// https://codingcompetitions.withgoogle.com/codejam/round/0000000000876ff1/0000000000a4621b

str solve(ll &R, ll &C)
{
    str rv = "..+";
    FOB(i, 1, C) rv += "-+";
    rv += '\n';
    rv += "..|";
    FOB(i, 1, C) rv += ".|";
    rv += '\n';
    rv += "+";
    FOR(i, C) rv += "-+";
    rv += '\n';
    FOB(i, 1, R)
    {
        rv += '|';
        FOR(j, C) rv += ".|";
        rv += '\n';
        rv += "+";
        FOR(i, C) rv += "-+";
        rv += '\n';
    }
    return rv;
}

int main()
{
    ll T;
    cin >> T;
    FOR(t, T)
    {
        ll R, C;
        cin >> R >> C;
        cout << "Case #" << t + 1 << ":\n" << solve(R, C);
    }
    return 0;
}