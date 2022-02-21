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

int main()
{
    str t, rv;
    ll n;
    getline(cin, t);
    istringstream iss0(t);
    iss0 >> n;
    vvl m_e(n, vl(n)), m_t(1);
    FOR(i, n)
    {
        getline(cin, t);
        istringstream iss1(t);
        FOR(j, n) iss1 >> m_e[i][j];
    }
    getline(cin, t);
    FORE(c, t)
    {
        if(sz(m_t[sz(m_t) - 1]) == n) m_t.pb({});
        if(c >= 'A' && c <= 'Z') m_t[sz(m_t) - 1].pb(c - 'A');
        elif(c >= '0' && c <= '9') m_t[sz(m_t) - 1].pb(c - '0' + 26);
        elif(c >= ' ') m_t[sz(m_t) - 1].pb(36);
    }
    while(sz(m_t[sz(m_t) - 1]) != n) m_t[sz(m_t) - 1].pb(36);
    vvl m_r = m_t;
    FOR(i, sz(m_t))
    {
        FOR(j, n)
        {
            ll tmp = 0;
            FOR(k, n) tmp += m_e[j][k] * m_t[i][k];
            m_r[i][j] = tmp % 37;
        }
    }
    FORE(c, m_r)
    {
        FORE(x, c)
        {
            if(x < 26) rv.pb('A' + x);
            elif(x < 36) rv.pb('0' + (x - 26));
            elif(x == 36) rv.pb(' ');
        }
    }
    cout << rv << '\n';
    return 0;
}