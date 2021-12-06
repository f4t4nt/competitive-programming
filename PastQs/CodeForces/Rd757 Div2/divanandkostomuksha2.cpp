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

// https://codeforces.com/contest/1614/problem/D2

constexpr ll MAX = 2 * 1e7 + 1;

int main()
{
    ll N, rv = 0;
    cin >> N;
    vb refp(MAX, true);
    FOB(i, 2, sqrt(MAX) + 1) { if(refp[i]) { for(ll j = 2 * i; j <= MAX; j += i) { refp[j] = false; } } }
    vl p, ref(MAX), dp(MAX);
    FOB(i, 2, MAX) { if(refp[i]) { p.pb(i); } }
    FOR(n, N)
    {
        ll a;
        cin >> a;
        ref[a]++;
    }
    FORE(i, p) { FORR(j, MAX / i + 1) { if(!j) { break; } ref[j] += ref[i * j]; } }
    FORR(i, MAX)
    {
        if(!i) { break; }
        dp[i] = i * ref[i];
        // for(ll j = 2 * i; j < MAX; j += i) { dp[i] = max(dp[i], dp[j] + i * (ref[i] - ref[j])); }
        ll j = 0;
        while(j < sz(p) && p[j] * i < MAX) { dp[i] = max(dp[i], dp[p[j] * i] + i * (ref[i] - ref[p[j] * i])); j++; }
        rv = max(rv, dp[i]);
    }
    cout << rv << endl;
}