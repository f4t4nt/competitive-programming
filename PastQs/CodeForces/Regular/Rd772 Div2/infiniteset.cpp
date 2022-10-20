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
using mlb = map<ll, bool>;
using mpllb = map<pll, bool>;
using vmll = vector<mll>;
using ql = queue<ll>;
using qpll = queue<pll>;
using fl = long double;
using vf = vector<fl>;
using vvf = vector<vf>;
using vch = vector<char>;
using vvch = vector<vch>;
using mchvpll = map<char, vpll>;
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

// https://codeforces.com/contest/1635/problem/D

constexpr ll MOD = 1e9 + 7;

bool valid(ll x, vl &a0, bool tmp)
{
    if(tmp && binary_search(a0.begin(), a0.end(), x)) return false;
    elif(x == 0) return true;
    elif(x % 4 == 0) return valid(x / 4, a0, true); 
    elif(x % 2 == 1) return valid((x - 1) / 2, a0, true);
    else return true;
}

ll bitsize(ll &x)
{
    ll rv = 0;
    while(x)
    { x /= 2; rv++; }
    return rv;
}

int main()
{
    ll n, p, rv = 0;
    cin >> n >> p;
    vl a0(n), a1, refp0(p + 1), refp1(p + 1);
    FOR(i, n) cin >> a0[i];
    ssort(a0);
    FOR(i, n) if(valid(a0[i], a0, false)) a1.pb(a0[i]);
    refp0[p] = 1;
    refp0[p - 1] = 1;
    FORR(i, p - 1) refp0[i] = (refp0[i + 2] + refp0[i + 1]) % MOD;
    refp1[p] = 1;
    FORR(i, p) refp1[i] = (refp0[i] + refp1[i + 1]) % MOD;
    FORE(a, a1)
    {
        ll q = bitsize(a);
        if(q <= p) rv = (rv + refp1[q]) % MOD;
    }
    cout << rv << '\n';
    return 0;
}