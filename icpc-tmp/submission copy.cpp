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

const ld ERR = 1e-12;

ld dist(pair<ld, ld> v0, pair<ld, ld> v1)
{
    ld dx = v0.first - v1.first, dy = v0.second - v1.second;
    return sqrt(dx * dx + dy * dy);
}

pair<ld, ld> s2v(ld &mid, ll &i, vector<ld> &s, vector<pair<ld, ld>> &v)
{
    ld w = (s[i] - mid) / (s[i] - s[i - 1]);
    return make_pair(v[i % sz(v)].first * (1.0 - w) + v[(i - 1 + sz(v)) % sz(v)].first * w,
        v[i % sz(v)].second * (1.0 - w) + v[(i - 1 + sz(v)) % sz(v)].second * w);
}

ld shoelace(vector<pair<ld, ld>> &v)
{
    ld s1 = 0.0, s2 = 0.0;
    for(ll i = 0; i < sz(v); i++)
    {
        s1 += v[i].first * v[(i + 1) % sz(v)].second;
        s2 += v[i].second * v[(i + 1) % sz(v)].first;
    }
    ld rv = abs(s1 - s2) / 2.0;
    return rv;
}

int main()
{
    ll n;
    cin >> n;
    vector<pair<ld, ld>> v(n);
    FOR(i, n) cin >> v[i].first >> v[i].second;
    ld a = shoelace(v);
    vector<ld> s(n + 1);
    FOR(i, n) s[i + 1] = s[i] + dist(v[i], v[(i + 1) % sz(v)]);
    ld lo = 0, hi = s[n];
    while((hi - lo) / lo > ERR)
    {
        ld mid = (hi + lo) / 2;
        ll i = upper_bound(s.begin(), s.end(), mid) - s.begin();
        vector<pair<ld, ld>> vp(v.begin(), v.begin() + i);
        pair<ld, ld> p = s2v(mid, i, s, v);
        vp.pb(p);
        ld ap = shoelace(vp);
        if(ap * 2.0 > a) hi = mid;
        else lo = mid;
    }
    ll i = 0;
    while(s[i] < lo) i++;
    pair<ld, ld> p = s2v(lo, i, s, v);
    cout << setprecision(12) << p.first << ' ' << p.second << '\n';
    return 0;
}