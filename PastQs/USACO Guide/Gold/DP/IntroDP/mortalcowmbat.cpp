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

// http://www.usaco.org/index.php?page=viewproblem2&cpid=971

int main()
{
    ifstream cin("cowmbat.in");
    ofstream cout("cowmbat.out");

    ll N, M, K;
    cin >> N >> M >> K;
    vl S(N);
    FOR(n, N)
    {
        char c;
        cin >> c;
        S[n] = c - 'a';
    }
    vvl A(M, vl(M));
    FOR(m1, M) { FOR(m2, M) { cin >> A[m1][m2]; } }
    FOR(m1, M) { FOR(m2, M) { FOR(m3, M) { A[m2][m3] = min(A[m2][m3], A[m2][m1] + A[m1][m3]); } } }
    N++;
    vvl ref(M, vl(N));
    FOR(m, M) { FOB(n, 1, N) { ref[m][n] = ref[m][n - 1] + A[S[n - 1]][m]; } }
    M++;
    vvl dp(N, vl(M, 1e18));
    dp[0][0] = 0;
    FOB(n, K, N)
    {
        FOB(m, 1, M)
        {
            dp[n][m] = min(dp[n][m],
                min(dp[n - K][0] + ref[m - 1][n] - ref[m - 1][n - K],
                    dp[n - 1][m] + A[S[n - 1]][m - 1]));
            dp[n][0] = min(dp[n][0], dp[n][m]);
        }
    }
    cout << dp[N - 1][0] << endl;
}