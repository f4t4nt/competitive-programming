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
#define FOR(x, e) for(ll  x = 0; x < (ll) (e); x++)
#define FORR(x, e) for(ll x = (ll) (e) - 1; x >= (ll) (0); x--)
#define FOB(x, b, e) for(auto x = (b); x != (e); x++)
#define FOE(x, e, b) for(auto x = (ll) (e) - 1; x >= (b); x--)
#define FOI(x, e, i) for(ll x = 0; x < (ll) (e); x += (ll) (i))
#define FORE(x, C) for(auto& x : C)

using namespace std;

// http://www.usaco.org/index.php?page=viewproblem2&cpid=670

ll calcE(pll &c1, pll &c2)
{
    ll dx = c1.first - c2.first, dy = c1.second - c2.second;
    return dx * dx + dy * dy;
}

int main()
{
    ifstream cin("checklist.in");
    ofstream cout("checklist.out");

    ll H, G;
    cin >> H >> G;
    vpll Hc(H), Gc(G);
    FOR(h, H) { cin >> Hc[h].first >> Hc[h].second; }
    FOR(g, G) { cin >> Gc[g].first >> Gc[g].second; }
    H++; G++;
    vvl E(H, vl(G));
    FOR(h, H)
    {
        FOR(g, G)
        {
            if(h > 0 && g > 0)
            { E[h][g] = calcE(Hc[h - 1], Gc[g - 1]); }
            elif(g > 0)
            { E[0][g] = calcE(Gc[g - 1], Gc[g - 2]); }
            elif(h > 0)
            { E[h][0] = calcE(Hc[h - 1], Hc[h - 2]); }
        }
    }
    vvvl dp(2, vvl(H, vl(G, 1e18)));
    dp[0][1][0] = 0;
    FOR(h, H)
    {
        FOR(g, G)
        {
            if(h > 0 && g > 0)
            {
                dp[0][h][g] = min(dp[0][h][g], dp[1][h - 1][g] + E[h][g]);
                dp[1][h][g] = min(dp[1][h][g], dp[0][h][g - 1] + E[h][g]);
            }
            if(h > 1) { dp[0][h][g] = min(dp[0][h][g], dp[0][h - 1][g] + E[h][0]); }
            if(g > 1) { dp[1][h][g] = min(dp[1][h][g], dp[1][h][g - 1] + E[0][g]); }
        }
    }
    cout << dp[0][H - 1][ G - 1] << endl;
}