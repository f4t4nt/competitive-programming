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
#define FOB(x, b, e) for(auto x = b; x != e; x++)
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

// https://codeforces.com/contest/1644/problem/D

constexpr ll MOD = 998244353;

ll pow(ll x, ll y)
{
    if(!y) return 1;
    ll rv = pow(x, y / 2);
    rv = (rv * rv) % MOD;
    if(y % 2) rv = (rv * x) % MOD;
    return rv;
}

int main()
{
    ll t;
    cin >> t;
    while(t--)
    {
        ll n, m, k, q, rv = 0;
        cin >> n >> m >> k >> q;
        vector<pair<ll, ll>> que(q);
        FOR(i, q) cin >> que[i].first >> que[i].second;
        set<ll> refx, refy;
        FORR(i, q)
        {
            ll &x = que[i].first, &y = que[i].second;
            if(refx.find(x) != refx.end() && refy.find(y) != refy.end()) continue;
            rv++;
            refx.insert(x);
            refy.insert(y);
            if(sz(refx) == n || sz(refy) == m) break;
        }
        cout << pow(k, rv) << '\n';
    }
    return 0;
}