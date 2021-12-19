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
#define fl float
#define vf vector<fl>
#define vvf vector<vf>
#define str string
#define vstr vector<str>
#define mstrl map<str, ll>
    
#define pb push_back
#define mp make_pair
#define elif else if
#define sz(x) (ll) x.size()
#define ssort(x) sort(x.begin(), x.end())
#define rsort(x) sort(x.begin(), x.end(), greater<>())
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

// https://codeforces.com/contest/1316/problem/E

ll bitcount(ll x)
{
	ll rv = 0;
	while(x > 0) { rv++; x &= (x - 1); }
	return rv;
}

int main()
{
	ll N, P, K;
	cin >> N >> P >> K;
	vpll A(N);
	FOR(n, N) { cin >> A[n].first; A[n].second = n; }
	rsort(A);
	vvl S(N, vl(P));
	FOR(n, N) { FOR(p, P) { cin >> S[n][p]; } }
	N++;
	vvl dp(N, vl(1 << P, -1e18));
	dp[0][0] = 0;
	FOB(n, 1, N)
	{
		FOR(x, 1 << P)
		{
			dp[n][x] = dp[n - 1][x];
			if(n - bitcount(x) <= K)
			{ dp[n][x] += A[n - 1].first; }
			FOR(p, P)
			{ if(x & (1 << p)) { dp[n][x] = max(dp[n - 1][x ^ (1 << p)] + S[A[n - 1].second][p], dp[n][x]); } }
		}
	}
	N--;
	cout << dp[N][(1 << P) - 1] << '\n';
}