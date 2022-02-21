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

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using ull = unsigned long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using vvvvl = vector<vvvl>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using plvpll = pair<ll, vpll>;
using plvl = pair<ll, vl>;
using vplvl = vector<plvl>;
using sl = set<ll>;
using spll = set<pll>;
using vsl = vector<sl>;
using ssl = set<sl>;
using plsl = pair<ll, sl>;
using vplsl = vector<plsl>;
using plspll = pair<ll, spll>;
using msl = multiset<ll>;
using mspll = multiset<pll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using plvb = pair<ll, vb>;
using mll = map<ll, ll>;
using mlll = map<ll, mll>;
using mlvl = map<ll, vl>;
using mlpll = map<ll, pll>;
using mplll = map<pll, ll>;
using mlvpll = map<ll, vpll>;
using mlsl = map<ll, sl>;
using mpllb = map<pll, bool>;
using vmll = vector<mll>;
using ql = queue<ll>;
using qpll = queue<pll>;
using fl = long double;
using vf = vector<fl>;
using vvf = vector<vf>;
using str = string;
using vstr = vector<str>;
using mstrl = map<str, ll>;
using mcl = map<char, ll>;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())
#define max_elem(C) *max_element(C.begin(), C.end())
#define min_elem(C) *min_element(C.begin(), C.end())
#define contains(C, x) find(C.begin(), C.end(), x) != C.end()

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = (ll) b; x != (ll) e; x++)
#define FOE(x, e, b) for(auto x = (ll) e - 1; x != (ll) b; x--)
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

// https://judge.yosupo.jp/problem/maximum_independent_set

ll bitcount(ll x)
{
	ll rv = 0;
	while(x > 0) { rv++; x &= (x - 1); }
	return rv;
}

int main()
{
    ll n, m, rv = 0;
    cin >> n >> m;
    ll a = n / 2;
    ll b = n - a;
    vpll g(n);
    FOR(i, m)
    {
        ll u, v;
        cin >> u >> v;
        if(v < a) g[u].first |= (1 << v);
        else g[u].second |= (1 << (v - a));
        if(u < a) g[v].first |= (1 << u);
        else g[v].second |= (1 << (u - a));
    }
    vpll dp(1 << b);
    FOR(x, 1 << b)
    {
        FOR(i, b)
        {
            if(!(x & (1 << i))) continue;
            ll x0 = x ^ (1 << i);
            ll tmp = 1 + dp[x0 ^ (x0 & g[a + i].second)].first;
            if(tmp > dp[x].first)
            {
                dp[x].first = tmp;
                dp[x].second = dp[x0 ^ (x0 & g[a + i].second)].second | (1 << i);
            }
            tmp = dp[x0].first;
            if(tmp > dp[x].first)
            {
                dp[x].first = tmp;
                dp[x].second = dp[x0].second;
            }
        }
    }
    pll ref;
    FOR(x, 1 << a)
    {
        ll y = (1 << b) - 1;
        bool valid = true;
        FOR(i, a)
        {
            if(!(x & (1 << i))) continue;
            if(x & g[i].first)
            { valid = false; break; }
            y ^= (y & g[i].second);
        }
        if(!valid) continue;
        ll tmp = bitcount(x) + dp[y].first;
        if(tmp > rv)
        {
            rv = tmp;
            ref.first = x;
            ref.second = dp[y].second;
        }
    }
    cout << rv << '\n';
    FOR(i, a) if(ref.first & (1 << i)) cout << i << ' ';
    FOR(i, b) if(ref.second & (1 << i)) cout << a + i << ' ';
    cout << '\n';
    return 0;
}