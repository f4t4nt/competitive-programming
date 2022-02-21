#include <algorithm>
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
#define vl vector<ll>
#define vvl vector<vl>
#define vvvl vector<vvl>
#define vpll vector<pll>
#define vvpll vector<vpll>
#define sl set<ll>
#define spll set<pll>
#define msl multiset<ll>
#define mspll multiset<pll>
#define vb vector<bool>
#define vvb vector<vector<bool>>
#define mll map<ll, ll>
#define mlll map<ll, mll>
#define mlvl map<ll, vl>
#define mlsl map<ll, sl>
#define vmll vector<mll>
#define ql queue<ll>
#define str string
#define vstr vector<str>
#define pb push_back
#define elif else if

#define sz(x) (ll) x.size()
#define vsort(x) sort(x.begin(), x.end())
#define last_elem(coll) (*(coll.rbegin()))
#define FIND(x, v) find(x.begin(), x.end(), v)
#define FOR(x, e) for(ll  x = 0; x < (ll) (e); x++)
#define FORR(x, e) for(ll x = (ll) (e) - 1; x >= (ll) (0); x--)
#define FOB(x, b, e) for(auto x = (b); x != (e); x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) (e); x += (ll) (i))
#define FORE(x, C) for(auto& x : C)

using namespace std;

// https://open.kattis.com/problems/flexible

int main()
{
    ll W, P;
    cin >> W >> P;
    vb rv(101);
    vl part(P + 2);
    part[0] = 0;
    part[P + 1] = W;
    FOR(p, P) { cin >> part[p + 1]; }
    FOR(p, P + 2) { FOB(q, p + 1, P + 2) { rv[part[q] - part[p]] = true; } }
    FOB(i, 1, 101) { if(rv[i]) { cout << i << " "; }}
}