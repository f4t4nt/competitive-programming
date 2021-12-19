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
#define mlsl map<ll, sl>
#define mpllb map<pll, bool>
#define vmll vector<mll>
#define ql queue<ll>
#define qpll queue<pll>
#define str string
#define vstr vector<str>
#define mstrl map<str, ll>

#define pb push_back
#define elif else if
#define sz(x) (ll) x.size()
#define vsort(x) sort(x.begin(), x.end())
#define last_elem(C) (*(C.rbegin()))
#define max_elem(C) (*max_element(C.begin(), C.end()))
#define min_elem(C) (*min_element(C.begin(), C.end()))

#define FIND(x, v) find(x.begin(), x.end(), v)
#define FOR(x, e) for(ll  x = 0; x < (ll) (e); x++)
#define FORR(x, e) for(ll x = (ll) (e) - 1; x >= (ll) (0); x--)
#define FOB(x, b, e) for(auto x = (b); x != (e); x++)
#define FOE(x, e, b) for(auto x = (ll) (e) - 1; x >= (b); x--)
#define FOI(x, e, i) for(ll x = 0; x < (ll) (e); x += (ll) (i))
#define FORE(x, C) for(auto& x : C)

#define MOD 1000000007

using namespace std;

// https://cses.fi/problemset/task/1746/

int main()
{
    ll N, M, rv = 0;
    cin >> N >> M;
    vl X(N);
    FOR(n, N) { cin >> X[n]; }
    M++;
    vvl dp(N, vl(M + 1));
    if(X[0] == 0) { FOB(m, 1, M) { dp[0][m] = 1; } }
    else { dp[0][X[0]] = 1; }
    FOB(n, 1, N)
    {
        if(X[n] == 0)
        { FOB(m, 1, M) { dp[n][m] = (dp[n - 1][m - 1] + dp[n - 1][m] + dp[n - 1][m + 1]) % MOD; } }
        else
        { dp[n][X[n]] = (dp[n - 1][X[n] - 1] + dp[n - 1][X[n]] + dp[n - 1][X[n] + 1]) % MOD; }
    }
    FOR(m, M) { rv += dp[N - 1][m]; }
    cout << rv % MOD << endl;
}