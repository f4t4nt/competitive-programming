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
using plvl = pair<ll, vl>;
using vplvl = vector<plvl>;
using sl = set<ll>;
using spll = set<pll>;
using vsl = vector<sl>;
using ssl = set<sl>;
using plsl = pair<ll, sl>;
using vplsl = vector<plsl>;
using msl = multiset<ll>;
using mspll = multiset<pll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using mll = map<ll, ll>;
using mlll = map<ll, mll>;
using mlvl = map<ll, vl>;
using mlpll = map<ll, pll>;
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

constexpr ll MOD = 1e9 + 7;

// https://cses.fi/problemset/task/1080

int main()
{
    str S;
    cin >> S;
    ll N = sz(S);
    vvl choose(N / 2 + 1, vl(N / 2 + 1));
    choose[0][0] = 1;
    FOB(n, 1, N / 2 + 1)
    {
        choose[n][0] = true;
        FOB(m, 1, n + 1)
        {
            choose[n][m] = choose[n - 1][m] + choose[n - 1][m - 1];
            choose[n][m] %= MOD;
        }
    }
    vvl dp(N, vl(N));
    FOB(x, 1, N)
    {
        FOR(n, N - x)
        {
            if(x == 1)
            {
                if(S[n] == S[n + x])
                {
                    dp[n][n + x] = 1;
                    dp[n + x][n] = 1;
                }
            }
            else
            {
                if(S[n] == S[n + x])
                { dp[n][n + x] = dp[n + 1][n + x - 1]; }
                FOB(m, n + 1, n + x)
                {
                    if(S[n] == S[m])
                    { 
                        ll tmp = dp[n + 1][m - 1] * dp[m + 1][n + x];
                        tmp %= MOD;
                        tmp *= choose[(x + 1) / 2][(m - n + 1) / 2];
                        tmp %= MOD;
                        dp[n][n + x] += tmp;
                        dp[n][n + x] %= MOD;
                    }
                }
            }
        }
    }
    cout << dp[0][N - 1];
    return 0;
}