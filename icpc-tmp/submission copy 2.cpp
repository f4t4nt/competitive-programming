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

ll binsearch(vector<ll> &r, ll lo, ll hi, ll v, bool top)
{
    ll mid, w;
    while(hi - lo > 0)
    {
        mid = lo + (hi - lo + 1) / 2;
        w = r[mid];
        if(w >= v) lo = mid;
        else hi = mid - 1;
    }
    w = r[lo];
    if(w == v) return lo;
    elif(!top) return lo;
    else
    {
        while(r[lo] > v) lo++;
        return lo;
    }
}

int main()
{
    ll n, k, rv = 0;
    cin >> n >> k;
    vector<ll> r(1 << n);
    FOR(i, 1 << n) cin >> r[i];
    rsort(r);
    r.insert(r.begin(), 0);
    FOR(i, n)
    {
        ll x0 = 1 << i;
        ll y1 = x0 + 1;
        ll a0 = r[x0], b1 = r[y1];
        ll b0 = a0 - k, a1 = b1 + k;
        if(a0 > a1 || b0 > b1) continue;
        ll y0 = binsearch(r, x0 + 1, 2 * x0, b0, false);
        ll x1 = binsearch(r, 1, x0, a1, true);
        rv += min(abs(x1 - x0), abs(y1 - y0)) + 1;
    }
    cout << rv << '\n';
    return 0;
}