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
#define mcl map<char, ll>

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())
#define max_elem(C) *max_element(C.begin(), C.end())
#define min_elem(C) *min_element(C.begin(), C.end())

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = (ll) b; x != (ll) e; x++)
#define FOE(x, e, b) for(auto x = (ll) e - 1; x != (ll) b; x--)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto& x : C)

using namespace std;

// https://codeforces.com/contest/1612/problem/E

constexpr ll MAXK = 21;

int main()
{
    ll N, rv = 0;
    cin >> N;
    mll ref0, ref1;
    vpll A(N);
    FOR(n, N)
    {
        ll m, k;
        cin >> m >> k;
        if(!ref0[m])
        { ref0[m] = sz(ref0); }
        A[n] = { ref0[m] - 1, k };
    }
    FORE(r, ref0)
    { r.second--; ref1[r.second] = r.first; }
    ll M = sz(ref0);
    vector<pair<fl, vl>> ref2(MAXK);
    FOB(k, 1, min(M + 1, MAXK))
    {
        vector<pair<fl, ll>> tmp(M);
        FOR(n, N)
        { tmp[A[n].first].first += min((fl) 1, (fl) A[n].second / k); tmp[A[n].first].second = A[n].first; }
        rsort(tmp);
        FOR(x, k)
        { ref2[k].first += tmp[x].first; ref2[k].second.pb(tmp[x].second); }
        if(ref2[k].first > ref2[rv].first)
        { rv = k; }
    }
    cout << rv << '\n';
    FORE(r, ref2[rv].second)
    { cout << ref1[r] << ' '; }
    cout << '\n';
}