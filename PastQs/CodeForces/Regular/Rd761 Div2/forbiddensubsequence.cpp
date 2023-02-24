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

// https://codeforces.com/contest/1617/problem/A

void printStr(vl &S)
{
	FOR(s, sz(S))
	{
		cout << (char) ('a' + S[s]);
	}
	cout << '\n';
	return;
}

bool subseq(vl &S, vl &T)
{
	ll t = 0;
	FOR(s, sz(S))
	{
		if(t == sz(T)) { return true; }
		if(S[s] == T[t]) { t++; }
	}
	if(t == sz(T)) { return true; }
	return false;
}

int main()
{
	ll T;
	cin >> T;
	while(T--)
	{
		str S, T;
		cin >> S >> T;
		vl Sv1, Tv1, Tv2;
		FOR(s, sz(S)) { Sv1.pb(S[s] - 'a'); }
		FOR(t, sz(T)) { Tv1.pb(T[t] - 'a'); }
		Tv2 = Tv1;
		ssort(Sv1);
		ssort(Tv2);
		if(Tv1 != Tv2) { printStr(Sv1); }
		else
		{
			bool x = subseq(Sv1, Tv2);
			if(!x) { printStr(Sv1); }
			else
			{
				vl Sv2;
				ll bCnt = 0, s = 0;
				while(s < sz(Sv1) && Sv1[s] <= 2)
				{
					if(Sv1[s] == 1) { bCnt++; }
					else { Sv2.pb(Sv1[s]); }
					s++;
				}
				FOR(b, bCnt)
				{ Sv2.pb(1); }
				while(s < sz(Sv1))
				{ Sv2.pb(Sv1[s]); s++; }
				printStr(Sv2);
			}
		}
	}
}