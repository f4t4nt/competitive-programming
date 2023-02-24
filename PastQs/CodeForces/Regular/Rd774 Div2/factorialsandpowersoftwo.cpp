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

ll bitcount(ll x)
{
	ll rv = 0;
	while(x > 0) { rv++; x &= (x - 1); }
	return rv;
}

int main()
{
    ll t;
    cin >> t;
    vector<ll> fact = { 1, 2 };
    while(fact[sz(fact) - 1] < 1e12) fact.pb(fact[sz(fact) - 1] * (sz(fact) + 1));
    while(t--)
    {
        ll n, rv = 1e18;
        cin >> n;
        FOR(x, 1 << sz(fact))
        {
            ll m = 0;
            FOR(i, sz(fact)) if(x & (1 << i)) m += fact[i];
            if(m > n) continue;
            rv = min(rv, bitcount(x) + bitcount(n - m));
        }
        if(rv == 1e18) cout << -1 << '\n';
        else cout << rv << '\n';
    }
    return 0;
}