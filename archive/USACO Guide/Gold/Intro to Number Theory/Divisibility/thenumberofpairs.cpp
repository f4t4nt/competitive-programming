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
 
#define MAX (2e7 + 1)
 
using namespace std;

// https://codeforces.com/contest/1499/problem/D
 
int main()
{
    ll T;
    cin >> T;
    vl P(MAX), cP(MAX);
    FOB(i, 2, MAX) { if(P[i] == 0) { FOI(j, MAX, i) { P[j] = i; } } }
    P[0] = 0; P[1] = 1;
    FOB(i, 2, MAX)
    {
        ll j = i / P[i];
        cP[i] = cP[j];
        if(P[j] != P[i]) { cP[i]++; }
    }
    FOR(t, T)
    {
        ll C, D, X, rv = 0;
        cin >> C >> D >> X;
        ll sqrtX = sqrt(X) + 1;
        FOB(i, 1, sqrtX)
        {
            if(X % i == 0)
            {
                ll Y = i + D;
                if(Y % C == 0) { rv += 1 << cP[Y / C]; }
                if(i * i < X)
                {
                    Y = X / i + D;
                    if(Y % C == 0) { rv += 1 << cP[Y / C]; }
                }
            }
        }
        cout << rv << endl;
    }
}