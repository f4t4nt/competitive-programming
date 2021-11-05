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

#define LLONG_MAX 9223372036854775807

using namespace std;

int main()
{
    ifstream cin("snakes.in");
    ofstream cout("snakes.out");

    ll N, K;
    cin >> N >> K;
    vl A(N), S(N + 1);
    FOR(n, N) { cin >> A[n]; S[n + 1] = S[n] + A[n]; }
    vvl maxa(N, vl(N));
    FOR(i, N) { maxa[i][i] = A[i]; }
    FOB(s, 1, N) { FOR(i, N - s) { maxa[i][s + i] = max(maxa[i + 1][s + i], maxa[i][s + i - 1]); } }
    N++; K++;
    // total, length, height
    vvl dp(N, vl(K));
    FOB(n, 1, N)
    {
        dp[n][0] = n * maxa[0][n - 1] - S[n];
        FOB(k, 1, K)
        {
            ll mindp = LLONG_MAX;
            FOE(m, n + 1, 1) { mindp = min(dp[m - 1][k - 1] + maxa[m - 1][n - 1] * (n - m + 1) - S[n] + S[m - 1], mindp); }
            dp[n][k] = mindp;
        }
    }
    cout << dp[N - 1][K - 1] << endl;
}