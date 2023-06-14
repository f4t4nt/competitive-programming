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

// http://www.usaco.org/index.php?page=viewproblem2&cpid=673

constexpr ll MOD = 1e9 + 9;

int main()
{
    ifstream cin("team.in");
    ofstream cout("team.out");

	ll N, M, K;
	cin >> N >> M >> K;
	vl J(N), P(M);
	FOR(n, N) { cin >> J[n]; }
	FOR(m, M) { cin >> P[m]; }
	ssort(J);
	ssort(P);
	N++; M++; K++;
	vvvl dp(K, vvl(N, vl(M, MOD)));
	FOR(n, N) { FOR(m, M) { dp[0][n][m] = 1; } }
	FOB(k, 1, K)
	{
		FOB(n, 1, N)
		{
			FOB(m, 1, M)
			{
				dp[k][n][m] += dp[k][n - 1][m];
				dp[k][n][m] += dp[k][n][m - 1];
				dp[k][n][m] -= dp[k][n - 1][m - 1];
				if(J[n - 1] > P[m - 1])
				{ dp[k][n][m] += dp[k - 1][n - 1][m - 1]; }
				dp[k][n][m] %= MOD;
			}
		}
	}
	cout << dp[K - 1][N - 1][M - 1] << '\n';
}