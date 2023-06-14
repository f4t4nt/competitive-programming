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

// https://codeforces.com/contest/1591/problem/D

ll mergeInv(vl &A0, vl &A1, ll lo, ll mid, ll hi)
{
	ll i = lo, j = mid, k = lo, rv = 0;
	while(i < mid && j < hi)
	{
		if(A0[i] > A0[j])
		{
			A1[k++] = A0[j++];
			rv += mid - i;
		}
		else
		{ A1[k++] = A0[i++]; }
	}
	while(i < mid)
	{ A1[k++] = A0[i++]; }
	while(j < hi)
	{ A1[k++] = A0[j++]; }
	FOB(n, lo, hi)
	{ A0[n] = A1[n]; }
	return rv;
}

ll numInv(vl &A0, vl &A1, ll lo, ll hi)
{
	ll rv = 0;
	if(hi > lo)
	{
		ll mid = (lo + hi) / 2;
		rv += numInv(A0, A1, lo, mid);
		rv += numInv(A0, A1, mid + 1, hi);
		rv += mergeInv(A0, A1, lo, mid + 1, hi + 1);
	}
	return rv;
}

int main()
{
	ll T;
	cin >> T;
	while(T--)
	{
		ll N;
		cin >> N;
		sl S;
		vl A0(N), A1(N);
		FOR(n, N) { cin >> A0[n]; S.insert(A0[n]); }
		if(numInv(A0, A1, 0, N - 1) % 2 && sz(A0) == sz(S)) { cout << "NO\n"; }
		else { cout << "YES\n"; }
	}
}