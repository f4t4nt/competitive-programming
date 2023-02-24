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

// https://codeforces.com/contest/1651/problem/C

int main()
{
    ll t;
    cin >> t;
    while(t--)
    {
        ll n;
        cin >> n;
        vector<ll> a(n), b(n);
        FOR(i, n) cin >> a[i];
        FOR(i, n) cin >> b[i];
        if(n == 1) cout << abs(a[0] - b[0]) << '\n';
        else
        {
            ll x = abs(a[0] - b[0]), x0 = 1e18, x1 = 1e18,
                y = abs(a[n - 1] - b[n - 1]), y0 = 1e18, y1 = 1e18,
                z0 = abs(a[0] - b[n - 1]), z1 = abs(a[n - 1] - b[0]);
            FOR(i, n - 1) x0 = min(x0, abs(a[0] - b[i + 1]));
            FOR(i, n - 1) x1 = min(x1, abs(a[n - 1] - b[i]));
            FOR(i, n - 1) y0 = min(y0, abs(b[0] - a[i + 1]));
            FOR(i, n - 1) y1 = min(y1, abs(b[n - 1] - a[i]));
            x = min(x, x0 + y0);
            y = min(y, x1 + y1);
            cout << min(x + y,
                    min(z0 + z1,
                    min(z0 + y0 + x1,
                        z1 + x0 + y1))) << '\n';
        }
    }
    return 0;
}