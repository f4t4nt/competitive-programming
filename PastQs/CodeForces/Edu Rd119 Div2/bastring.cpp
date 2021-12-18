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

// https://codeforces.com/contest/1620/problem/C

int main()
{
	ll T;
	cin >> T;
	while(T--)
	{
		bool error = false;
		ll N, K, X;
		cin >> N >> K >> X;
		str S, rv;
		cin >> S;
		vl cntA, cntB;
		cntA.pb(-1);
		FOR(n, N)
		{
			if(S[n] == 'a' && (n == 0 || S[n - 1] == '*'))
			{ cntA.pb(1); }
			elif(S[n] == 'a')
			{ cntA[sz(cntA) - 1]++; }
			elif(S[n] == '*' && (n == 0 || S[n - 1] == 'a'))
			{ cntA.pb(0); cntB.pb(K); }
			elif(S[n] == '*')
			{ cntB[sz(cntB) - 1] += K; }
		}
		vl ref1(sz(cntB), 1e18 + 1), ref2(sz(cntB));
		if(cntB.size() > 0)
		{
			ref1[sz(ref1) - 1] = 1;
			FORR(i, sz(cntB) - 1)
			{
				if(log10((fl) (cntB[i + 1] + 1)) + log10((fl) (ref1[i + 1])) <= 18)
				{ ref1[i] = min(ref1[i], (cntB[i + 1] + 1) * ref1[i + 1]); }
				else
				{ break; }
			}
			X--;
			FOR(i, sz(ref1))
			{
				ref2[i] = X / ref1[i];
				X %= ref1[i];
				if(ref2[i] > cntB[i])
				{ cout << "ERROR\n"; error = true; break; }
			}
		}
		ll i = 0, j = 0;
		while(i < sz(cntA) && !error)
		{
			if(cntA[i] > 0)
			{ rv += string(cntA[i], 'a'); }
			elif(cntA[i] == 0 && j < sz(ref2))
			{
				rv += string(ref2[j], 'b');
				j++;
			}
			i++;
		}
		if(!error && j == sz(ref2))
		{ cout << rv << '\n'; }
	}
}