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

// https://codeforces.com/contest/1633/problem/D

int main()
{
    ll T;
    cin >> T;
    vvl ref0(15);
    vl ref1(1001, -1);
    ref0[0].pb(1);
    ref1[1] = 0;
    FOR(i, 14)
    {
        FOR(j, sz(ref0[i]))
        {
            FOB(x, 1, ref0[i][j] + 1)
            {
                ll y = ref0[i][j] + ref0[i][j] / x;
                if(y < 1001 && ref1[y] == -1)
                {
                    ref1[y] = i + 1;
                    ref0[i + 1].pb(y);
                }
            }
        }
    }
    while(T--)
    {
        ll N, K;
        cin >> N >> K;
        vl B(N), C(N), ref2(N);
        FOR(i, N) cin >> B[i];
        FOR(i, N) cin >> C[i];
        FOR(i, N) ref2[i] = ref1[B[i]];
        vl dp(15 * N, -1);
        dp[0] = 0;
        FOR(i, N)
        {
            FORR(j, 15 * N - ref2[i])
            {
                if(dp[j] == -1) continue;
                ll k = j + ref2[i];
                dp[k] = max(dp[k], dp[j] + C[i]);
            }
        }
        ll rv = 0;
        FOR(i, min(K + 1, 15 * N)) rv = max(rv, dp[i]);
        cout << rv << '\n';
    }
    return 0;
}