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
#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= (ll) 0; x--)
#define FOB(x, b, e) for(auto x = (ll) b; x != (ll) e; x++)
#define FOE(x, e, b) for(auto x = (ll) e - 1; x >= (ll) b; x--)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto& x : C)
 
using namespace std;

// http://www.usaco.org/index.php?page=viewproblem2&cpid=553

constexpr ll MOD = (1e9 + 7);

int main()
{
    ifstream cin("palpath.in");
    ofstream cout("palpath.out");

    ll N;
    cin >> N;
    vvl G(N, vl(N));
    FOR(n, N)
    {
        FOR(m, N)
        {
            char c;
            cin >> c;
            G[n][m] = c - 'A';
        }
    }
    vvl dp0(N, vl(N));
    FOR(n, N) { dp0[n][n] = 1; }
    // vvvl dp(N, vvl(N, vl(N)));
    // FOR(n, N) { dp[0][n][n] = 1; }
    FOB(n, 1, N)
    {
        vvl dp1(N, vl(N));

        FOR(r1, N)
        {
            // bool equal = dp[n - 1] == dp0;
            ll c1 = N - 1 - r1 - n;
            if(c1 < 0) { continue; }
            FOR(r2, N)
            {
                ll c2 = N - 1 - r2 + n;
                if(c2 >= N || G[r1][c1] != G[r2][c2]) { continue; }
                dp1[r1][r2] = dp0[r1][r2];
                if(r1 < N - 1)
                { dp1[r1][r2] += dp0[r1 + 1][r2]; }
                if(r2 > 0)
                { dp1[r1][r2] += dp0[r1][r2 - 1]; }
                if(r1 < N - 1 && r2 > 0)
                { dp1[r1][r2] += dp0[r1 + 1][r2 - 1]; }
                dp1[r1][r2] %= MOD;
                // dp[n][r1][r2] = dp[n - 1][r1][r2];
                // if(r1 < N - 1)
                // { dp[n][r1][r2] += dp[n - 1][r1 + 1][r2]; }
                // if(r2 > 0)
                // { dp[n][r1][r2] += dp[n - 1][r1][r2 - 1]; }
                // if(r1 < N - 1 && r2 > 0)
                // { dp[n][r1][r2] += dp[n - 1][r1 + 1][r2 - 1]; }
                // dp[n][r1][r2] %= MOD;
            }
        }
        swap(dp0, dp1);
    }
    N--;
    cout << dp0[0][N] << endl;
}