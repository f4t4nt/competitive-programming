#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
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
 
#define ll long long
#define pll pair<ll, ll>
#define vi vector<int>
#define vvi vector<vi>
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vpll vector<pll>
#define vvpll vector<vpll>
#define sl set<ll>
#define spll set<pll>
#define vsl vector<sl>
#define ssl set<sl>
#define plsl pair<ll, sl>
#define vplsl vector<plsl>
#define msl multiset<ll>
#define mspll multiset<pll>
#define vb vector<bool>
#define vvb vector<vb>
#define mll map<ll, ll>
#define mlll map<ll, mll>
#define mlvl map<ll, vl>
#define mlpll map<ll, pll>
#define mlvpll map<ll, vpll>
#define mlsl map<ll, sl>
#define mpllb map<pll, bool>
#define vmll vector<mll>
#define ql queue<ll>
#define qpll queue<pll>
#define str string
#define vstr vector<str>
#define mstrl map<str, ll>
 
#define pb push_back
#define mp make_pair
#define elif else if
#define sz(x) (ll) x.size()
#define vsort(x) sort(x.begin(), x.end())
#define last_elem(C) (*(C.rbegin()))
#define max_elem(C) (*max_element(C.begin(), C.end()))
#define min_elem(C) (*min_element(C.begin(), C.end()))
 
#define FIND(x, v) find(x.begin(), x.end(), v)
#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= (ll) 0; x--)
#define FOB(x, b, e) for(auto x = (ll) b; x != (ll) e; x++)
#define FOE(x, e, b) for(auto x = (ll) e - 1; x >= (ll) b; x--)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto& x : C)

using namespace std;

// https://cses.fi/problemset/task/1665/

constexpr ll MOD = (1e9 + 7);

int main()
{
    ll N, X, rv = 0;
    cin >> N >> X;
    vl T(N);
    FOR(n, N) { cin >> T[n]; }
    vsort(T);
    vvl dp0(51, vl(10001));
    dp0[0][5000] = 1;
    FORE(t, T)
    {
        vvl dp1(51, vl(10001));
        FOR(m, 51)
        {
            FOR(o, 10001)
            {
                if(dp0[m][o])
                {
                    if(m + 1 < 51) { dp1[m + 1][o - t] += dp0[m][o]; dp1[m + 1][o - t] %= MOD; }
                    dp1[m][o] += (m + 1) * dp0[m][o]; dp1[m][o] %= MOD;
                    if(m > 0) { dp1[m - 1][o + t] += m * dp0[m][o]; dp1[m - 1][o + t] %= MOD; }
                }
            }
        }
        swap(dp0, dp1);
    }
    FOB(i, 5000, 5000 + X + 1) { rv += dp0[0][i]; rv %= MOD; }
    cout << rv << endl;
}