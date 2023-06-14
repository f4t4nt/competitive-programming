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
#define fl float
#define vf vector<fl>
#define vvf vector<vf>
#define str string
#define vstr vector<str>
#define mstrl map<str, ll>

#define pb push_back
#define elif else if
#define sz(x) (ll) x.size()
#define ssort(x) sort(x.begin(), x.end())
#define rsort(x) sort(x.begin(), x.end(), greater<>())

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= (ll) 0; x--)
#define FOB(x, b, e) for(auto x = (ll) b; x != (ll) e; x++)
#define FOE(x, e, b) for(auto x = (ll) e - 1; x >= (ll) b; x--)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto& x : C)

using namespace std;

// http://www.usaco.org/index.php?page=viewproblem2&cpid=515

ll bitcount(ll x)
{
	ll rv = 0;
	while(x > 0) { rv++; x &= (x - 1); }
	return rv;
}

int main()
{
    ifstream cin("movie.in");
    ofstream cout("movie.out");

    ll N, L;
    cin >> N >> L;
    vplvl M(N);
    FOR(n, N)
    {
        ll C;
        cin >> M[n].first >> C;
        M[n].second = vl(C);
        FOR(c, C)
        { cin >> M[n].second[c]; M[n].second[c] *= -1; }
    }
    FOR(n, N)
    { reverse(M[n].second.begin(), M[n].second.end()); }
    ll rv = 1e18;
    vl dp(1 << N, -1);
    dp[0] = 0;
    FOR(x, 1 << N)
    {
        if(dp[x] < 0)
        { continue; }
        ll nv = bitcount(x) + 1;
        FOR(n, N)
        {
            if(x & (1 << n))
            { continue; }
            ll tmp = -*lower_bound(M[n].second.begin(), M[n].second.end(), -dp[x]) + M[n].first;
            if(tmp - M[n].first <= dp[x] && tmp >= dp[x])
            {
                dp[x | (1 << n)] = max(dp[x | (1 << n)], tmp);
                if(tmp >= L)
                { rv = min(rv, nv); }
            }
        }
    }
    if(rv < 1e18)
    { cout << rv << '\n'; }
    else
    { cout << "-1\n"; }
}