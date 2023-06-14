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

// https://codeforces.com/contest/1620/problem/B

int main()
{
	ll T;
	cin >> T;
	while(T--)
	{
		ll W, H, rv = 0;
		cin >> W >> H; 
		// x0 bottom, x1 top, y0 left, y1 right 
		ll Kx0, Kx1, Ky0, Ky1, minX = 1e18, maxX = 0, minY = 1e18, maxY = 0, minX0 = 1e18, maxX0 = 0, minY0 = 1e18, maxY0 = 0, minX1 = 1e18, maxX1 = 0, minY1 = 1e18, maxY1 = 0;
		cin >> Kx0;
		vl x0(Kx0);
		FOR(k, Kx0)
		{ cin >> x0[k]; minX0 = min(minX0, x0[k]); maxX0 = max(maxX0, x0[k]); }
		if(Kx0)
		{ minX = 0; }
		cin >> Kx1;
		vl x1(Kx1);
		FOR(k, Kx1)
		{ cin >> x1[k]; minX1 = min(minX1, x1[k]); maxX1 = max(maxX1, x1[k]); }
		if(Kx1)
		{ maxX = W; }
		cin >> Ky0;
		vl y0(Ky0);
		FOR(k, Ky0)
		{ cin >> y0[k]; minY0 = min(minY0, y0[k]); maxY0 = max(maxY0, y0[k]); }
		if(Ky0)
		{ minY = 0; }
		cin >> Ky1;
		vl y1(Ky1);
		FOR(k, Ky1)
		{ cin >> y1[k]; minY1 = min(minY1, y1[k]); maxY1 = max(maxY1, y1[k]); }
		if(Ky1)
		{ maxY = H; }
		rv = max(rv, max(maxY, max(maxY0, maxY1)) * (maxX0 - minX0));
		rv = max(rv, max(H - minY, max(H - minY0, H - minY1)) * (maxX1 - minX1));
		rv = max(rv, max(maxX, max(maxX0, maxX1)) * (maxY0 - minY0));
		rv = max(rv, max(W - minX, max(W - minX0, W - minX1)) * (maxY1 - minY1));
		cout << rv << '\n';
	}
}