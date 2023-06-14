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

// https://codeforces.com/contest/1649/problem/C

ll manhattan1d(vector<ll> &ref)
{
    ssort(ref);
    ll rv = 0, s = 0;
    FOR(i, sz(ref))
    {
        rv += ref[i] * i - s;
        s += ref[i];
    }
    return rv;
}

ll manhattan(vector<ll> &refx, vector<ll> &refy)
{
    return manhattan1d(refx) + manhattan1d(refy);
}

int main()
{
    ll n, m, rv = 0;
    cin >> n >> m;
    vector<vector<ll>> refx(1e5), refy(1e5);
    vector<vector<ll>> g(n, vector<ll>(m));
    FOR(i, n)
    {
        FOR(j, m)
        {
            cin >> g[i][j];
            g[i][j]--;
            refx[g[i][j]].pb(i);
            refy[g[i][j]].pb(j);
        }
    }
    FOR(i, 1e5) rv += manhattan(refx[i], refy[i]);
    cout << rv << '\n';
    return 0;
}