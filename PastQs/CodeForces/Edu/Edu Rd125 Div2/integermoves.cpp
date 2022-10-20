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

// https://codeforces.com/contest/1657/problem/A

int main()
{
    ll t;
    cin >> t;
    vector<pair<ll, ll>> ref;
    vector<vector<ll>> dp(51, vector<ll>(51, 1e9));
    FOR(x, 51)
    {
        FOR(y, 51)
        {
            ll z = sqrt((ld) (x * x + y * y));
            if (z * z == x * x + y * y) ref.pb({ x, y });
        }
    }
    dp[0][0] = 0;
    FOR(x, 51)
    {
        FOR(y, 51)
        {
            FORE(r, ref)
            {
                if(r.first > x || r.second > y) continue;
                dp[x][y] = min(dp[x][y], 1 + dp[x - r.first][y - r.second]);
            }
        }
    }
    while(t--)
    {
        ld x, y;
        cin >> x >> y;
        cout << dp[x][y] << '\n';
    }
    return 0;
}