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

#define ll long long
#define pll pair<ll, ll>
#define vi vector<int>
#define vvi vector<vi>
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vvvvl vector<vvvl>
#define vpll vector<pll>
#define vvpll vector<vpll>
#define plvl pair<ll, vl>
#define vplvl vector<plvl>
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
#define fl long double
#define vf vector<fl>
#define vvf vector<vf>
#define str string
#define vstr vector<str>
#define mstrl map<str, ll>
#define mcl map<char, ll>

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
#define FORE(x, C) for(auto& x : C)

using namespace std;

// https://open.kattis.com/problems/catandmice

constexpr fl ERR = 1e-6;

ll bitcount(ll x)
{
	ll rv = 0;
	while(x > 0) { rv++; x &= (x - 1); }
	return rv;
}

fl dist(fl x0, fl y0, fl x1, fl y1)
{
    fl dx = x0 - x1, dy = y0 - y1;
    return sqrt(dx * dx + dy * dy);
}

bool valid(fl &mid, ll &N, vvf &A, vf &pow)
{
    vvf dp(1 << N, vf(N, 1e18));
    FOR(n, N)
    {
        fl tmp = dist(A[n][0], A[n][1], 0, 0) / mid;
        if(tmp <= A[n][2])
        { dp[1 << n][n] = tmp; }
    }
    FOR(x, 1 << N)
    {
        fl v = mid * pow[bitcount(x)];
        FOR(n, N)
        {
            if(x & (1 << n))
            { continue; }
            FOR(m, N)
            {
                if(dp[x][m] == 1e18)
                { continue; }
                fl tmp = dp[x][m] + dist(A[n][0], A[n][1], A[m][0], A[m][1]) / v;
                if(tmp <= A[n][2])
                { dp[x | (1 << n)][n] = min(dp[x | (1 << n)][n], tmp); }
            }
        }
    }
    FOR(n, N)
    {
        if(dp[(1 << N) - 1][n] <= A[n][2])
        { return true; }
    }
    return false;
}

int main()
{
    ll N;
    cin >> N;
    vvf A(N, vf(3));
    FOR(n, N)
    { cin >> A[n][0] >> A[n][1] >> A[n][2]; }
    fl M;
    cin >> M;
    vf pow(N + 1, 1);
    FOR(n, N)
    { pow[n + 1] = pow[n] * M; }
    fl lo = 0, hi = 1e9;
    while(hi - lo > ERR)
    {
        fl mid = (hi + lo) / 2;
        if(valid(mid, N, A, pow))
        { hi = mid; }
        else
        { lo = mid; }
    }
    cout << fixed << setprecision(6) << lo << '\n';
}