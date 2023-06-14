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

// http://www.usaco.org/index.php?page=viewproblem2&cpid=598

ll calcE(pll &c1, pll &c2)
{
    ll dx = c1.first - c2.first, dy = c1.second - c2.second;
    return dx * dx + dy * dy;
}

int main()
{
    ifstream cin("radio.in");
    ofstream cout("radio.out");

    ll N, M;
    cin >> N >> M;
    N++; M++;
    vpll F(N), B(M);
    str Fseq, Bseq;
    cin >> F[0].first >> F[0].second >> B[0].first >> B[0].second >> Fseq >> Bseq;
    FOB(n, 1, N)
    {
        F[n] = F[n - 1];
        char &c = Fseq[n - 1];
        if(c == 'N') { F[n].second++; }
        elif(c == 'E') { F[n].first++; }
        elif(c == 'W') { F[n].first--; }
        elif(c == 'S') { F[n].second--; }
    }
    FOB(m, 1, M)
    {
        B[m] = B[m - 1];
        char &c = Bseq[m - 1];
        if(c == 'N') { B[m].second++; }
        elif(c == 'E') { B[m].first++; }
        elif(c == 'W') { B[m].first--; }
        elif(c == 'S') { B[m].second--; }
    }
    N++; M++;
    vvl dp(N, vl(M, 1e18));
    FOB(n, 1, N) { FOB(m, 1, M) { dp[n][m] = calcE(F[n - 1], B[m - 1]); } }
    dp[0][0] = 0; dp[1][1] = 0;
    FOB(n, 1, N) { FOB(m, 1, M) { dp[n][m] += min(dp[n - 1][m], min(dp[n][m - 1], dp[n - 1][m - 1])); } }
    cout << dp[N - 1][M - 1] << endl;
}