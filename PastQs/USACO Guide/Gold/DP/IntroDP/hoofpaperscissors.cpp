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
#define pb push_back
#define elif else if
 
#define sz(x) (ll) x.size()
#define vsort(x) sort(x.begin(), x.end())
#define last_elem(coll) (*(coll.rbegin()))
#define FOR(x, e) for(ll  x = 0; x < (ll) (e); x++)
#define FORR(x, e) for(ll x = (ll) (e) - 1; x < (ll)(e); x--)
#define FOB(x, b, e) for(auto x = (b); x != (e); x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) (e); x += (ll) (i))
#define FORE(x, C) for(auto& x : C)

using namespace std;

// http://www.usaco.org/index.php?page=viewproblem2&cpid=694

int main()
{
    ifstream cin("hps.in");
    ofstream cout("hps.out");

    ll N, K, rv = 0;
    cin >> N >> K;
    vl G(N + 9);
    vvvl dp(N + 9, vvl(K + 9, vl(3, 0)));
    FORE(g, G) {
        char ch;
        cin >> ch;
        if (ch == 'H') { g = 0; }
        elif (ch == 'P') { g = 1; }
        else { g = 2; }
    }

    FOR(n, N)
    {
        FOR(k, K + 1)
        {
            FOR(i, 3)
            {
                if(i == G[n]) { dp[n][k][i]++; }
                dp[n + 1][k + 1][0] = max(dp[n + 1][k + 1][0], dp[n][k][i]);
                dp[n + 1][k + 1][1] = max(dp[n + 1][k + 1][1], dp[n][k][i]);
                dp[n + 1][k + 1][2] = max(dp[n + 1][k + 1][2], dp[n][k][i]);
                dp[n + 1][k][i] = max(dp[n + 1][k][i], dp[n][k][i]);
            }
        }
    }

    FOR(i, 3) { rv = max(rv, dp[N - 1][K][i]); }
    cout << rv << endl;
    return 0;
}