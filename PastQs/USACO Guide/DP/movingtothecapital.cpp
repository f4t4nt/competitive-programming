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

// https://codeforces.com/contest/1472/problem/G

int main()
{
    ll T;
    cin >> T;
    FOR(t, T)
    {
        ll N, M;
        cin >> N >> M;
        mlvl R, S;
        FOR(m, M)
        {
            ll U, V;
            cin >> U >> V;
            R[U].pb(V);
            S[V].pb(U);
        }
        qpll bfs1, bfs2;
        bfs1.push({ 1, 0 });
        bfs2.push({ 1, 0 });
        vl D(N, N + 1);
        while(sz(bfs1) > 0)
        {
            if(D[bfs1.front().first - 1] > bfs1.front().second)
            {
                D[bfs1.front().first - 1] = bfs1.front().second;
                bfs1.front().second++;
                vl &Cr = R[bfs1.front().first];
                FORE(c, Cr) { bfs1.push({ c, bfs1.front().second }); }
            }
            bfs1.pop();
        }
        vl dp = D;
        qpll bfs2;
        // id, closest w action 2
        bfs2.push({ 1, 0 });
        mpllb states;
        while(sz(bfs2) > 0)
        {
            if(!states[bfs2.front()] && dp[bfs2.front().first - 1] >= bfs2.front().second)
            {
                dp[bfs2.front().first - 1] = bfs2.front().second;
                vl &Cs = S[bfs2.front().first];
                FORE(c, Cs)
                {
                    if(D[c - 1] >= D[bfs2.front().first - 1])
                    { bfs2.push({ c, D[bfs2.front().first - 1] }); }
                    else
                    { bfs2.push({ c, dp[bfs2.front().first - 1] }); }            
                }
                vl &Cr = R[bfs2.front().first];
                FORE(c, Cr) { bfs2.push({ c, D[c - 1] }); }
                states[bfs2.front()] = true;
            }
            bfs2.pop();
        }
        FORE(rv, dp) { cout << rv << " "; }
        cout << endl;
    }
}