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
#define MAXN_elem(C) *MAXN_element(C.begin(), C.end())
#define min_elem(C) *min_element(C.begin(), C.end())

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = (ll) b; x != (ll) e; x++)
#define FOE(x, e, b) for(auto x = (ll) e - 1; x != (ll) b; x--)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto& x : C)

using namespace std;

// https://szkopul.edu.pl/problemset/problem/lGqKS9urITMjTXhpdaHqyoEL/site/?key=statement

constexpr ll MAXN = 1e4 + 1;
constexpr ll MAXP = 350;

fl recurse(ll N, ll p, ll &P, vl &primes, vvf &dp, vvl &ref, vvb &done)
{
    if(p == P || primes[p] > N)
    { return 0; }
    if(done[N][p])
    { return dp[N][p]; }
    fl rv = recurse(N, p + 1, P, primes, dp, ref, done);
    ref[N][p] = 0;
    ll pow = primes[p], tmp = 1;
    while(pow <= N)
    {
        fl tv = tmp * log(primes[p]) + recurse(N - pow, p + 1, P, primes, dp, ref, done);
        if(rv < tv)
        { rv = tv; ref[N][p] = pow; }
        pow *= primes[p]; tmp++;
    }
    done[N][p] = true;
    return dp[N][p] = rv;
}

int main()
{
    ll D;
    cin >> D;
    vl primes;
    vb comps(MAXP);
    FOB(x, 2, MAXP)
    {
        if(!comps[x])
        {
            primes.pb(x);
            FOBI(m, 2 * x, MAXP, x)
            { comps[m] = true; }
        }
    }
    ll P = sz(primes);
    vvf dp(MAXN, vf(P));
    vvl ref1(MAXN, vl(P));
    vvb done(MAXN, vb(P));
    while(D--)
    {
        ll N;
        cin >> N;
        recurse(N, 0, P, primes, dp, ref1, done);
        vl rv(N);
        FOR(n, N)
        { rv[n] = n + 1; }
        vl ref2;
        FOR(p, P)
        {
            if(ref1[N][p])
            { ref2.pb(ref1[N][p]); }
            N -= ref1[N][p];
        }
        ssort(ref2);
        ll x = N, y = 0;
        while(x < sz(rv) && y < sz(ref2))
        {
            rotate(rv.begin() + x, rv.begin() + x + 1, rv.begin() + x + ref2[y]);
            x += ref2[y++];
        }
        FORE(r, rv)
        { cout << r << ' '; }
        cout << '\n';
    }
}