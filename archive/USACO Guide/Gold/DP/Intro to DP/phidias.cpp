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
#define vvb vector<vector<bool>>
#define mll map<ll, ll>
#define mlll map<ll, mll>
#define mlvl map<ll, vl>
#define mlsl map<ll, sl>
#define vmll vector<mll>
#define ql queue<ll>
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

// https://dmoj.ca/problem/ioi04p4

int main()
{
    ll W, H, N;
    cin >> W >> H >> N;
    vpll P(N);
    FOR(n, N) { cin >> P[n].first >> P[n].second; }
    W++; H++;
    vvl dp(H, vl(W));
    FOR(h, H) { FOR(w, W) { dp[h][w] = h * w; } }
    FOR(n, N) { dp[P[n].second][P[n].first] = 0; }
    FOB(h, 1, H)
    {
        FOB(w, 1, W)
        {
            FOB(y, 1, h + 1) { dp[h][w] = min(dp[h][w], dp[y][w] + dp[h - y][w]); }
            FOB(x, 1, w + 1) { dp[h][w] = min(dp[h][w], dp[h][x] + dp[h][w - x]); }
        }
    }
    cout << dp[H - 1][W - 1] << endl;
}