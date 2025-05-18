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

// http://www.usaco.org/index.php?page=viewproblem2&cpid=993

int main()
{
    ifstream cin("time.in");
    ofstream cout("time.out");

    ll N, M, C, rv = 0;
    cin >> N >> M >> C;
    vl V(N);
    vvl E(N), dp(1001, vl(N));
    vvb dp_bool(1001, vb(N));
    dp_bool[0][0] = true;
    FOR(n, N) { cin >> V[n]; }
    FOR(m, M)
    {
        ll a, b;
        cin >> a >> b;
        E[b - 1].pb(a - 1);
    }
    FOB(i, 1, 1001)
    {
        FOR(n, N)
        {
            FORE(e, E[n])
            {
                if(dp_bool[i - 1][e])
                {
                    dp[i][n] = max(dp[i][n], dp[i - 1][e] + V[n]);
                    dp_bool[i][n] = true; 
                }
           }
        }

        rv = max(rv, dp[i][0] - C * i * i);
    }
    cout << rv << endl;
    return 0;
}