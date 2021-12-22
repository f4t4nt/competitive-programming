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
#define FOE(x, e, b) for(auto x = (ll) e - 1; x >= (ll) b; x--)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto& x : C)

using namespace std;

// http://www.usaco.org/index.php?page=viewproblem2&cpid=897

constexpr ll MOD = 1e9 + 7;

ll pow(ll a, ll b)
{
    if(!b)
    { return 1; }
    elif(b == 1)
    { return a; }
    ll rv = pow(a, b / 2);
    rv = (rv * rv + MOD) % MOD;
    if(b % 2) { rv = (rv * a + MOD) % MOD; }
    return rv;
}

int main()
{
    ifstream cin("poetry.in");
    ofstream cout("poetry.out");

    ll N, M, K, maxE = 0, rv = 1;
    cin >> N >> M >> K;
    vpll W(N);
    FOR(n, N)
    { cin >> W[n].first >> W[n].second; }
    vl L(26);
    FOR(m, M)
    {
        char e;
        cin >> e;
        L[e - 'A']++;
        maxE = max(maxE, L[e - 'A']);
    }
    vl dp(K + 1), ref(N + 1);
    dp[0] = 1;
    FOR(k, K)
    {
        FOR(n, N)
        {
            if(W[n].first <= k)
            { dp[k] = (dp[k] + dp[k - W[n].first] + MOD) % MOD; }
        }
    }
    FOR(n, N)
    { ref[W[n].second] = (ref[W[n].second] + dp[K - W[n].first] + MOD) % MOD; }
    FOR(i, 26)
    {
        ll tmp = 0;
        if(L[i])
        {
            FOB(n, 1, N + 1)
            {
                if(ref[n])
                { tmp = (tmp + pow(ref[n], L[i]) + MOD) % MOD; }
            }
            rv = (rv * tmp + MOD) % MOD;
        }
    }
    cout << rv << '\n';
}