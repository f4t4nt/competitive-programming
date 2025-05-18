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
#define last_elem(coll) (*(coll.rbegin()))

#define FIND(x, v) find(x.begin(), x.end(), v)
#define FOR(x, e) for(ll  x = 0; x < (ll) (e); x++)
#define FORR(x, e) for(ll x = (ll) (e) - 1; x >= (ll) (0); x--)
#define FOB(x, b, e) for(auto x = (b); x != (e); x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) (e); x += (ll) (i))
#define FORE(x, C) for(auto& x : C)

using namespace std;

// http://www.usaco.org/index.php?page=viewproblem2&cpid=863

ll getElem(vl &S, vvl &dp, vvl &rv, ll &n, ll &k)
{
    ll tmp1 = 0;
    if(k > n + 1) { return 0; }
    elif(k <= n) { tmp1 = rv[n - k][0]; }
    ll tmp2 = dp[n - k + 1][k - 1];
    return tmp1 + max(S[n], tmp2) * k;
}

int main()
{
    ifstream cin("teamwork.in");
    ofstream cout("teamwork.out");

    ll N, K;
    cin >> N >> K;
    vl S(N);
    vvl dp(N, vl(K + 1, 0)), rv(N, vl(K + 1, 0));
    FOR(n, N) { cin >> S[n]; }
    FOR(k, K) { S.pb(0); }
    FOR(n, N) { FOB(k, 1, K + 1) { dp[n][k] = max(dp[n][k - 1], S[n + k - 1]); } }
    rv[0][0] = S[0]; rv[0][1] = S[0];
    FOB(n, (ll) 1, N)
    {
        FOB(k, (ll) 1, K + 1)
        {
            rv[n][k] = getElem(S, dp, rv, n, k);
        }
        rv[n][0] = *max_element(rv[n].begin(), rv[n].end());
    }
    cout << rv[N - 1][0] << endl;
}