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
#define mcl map<char, ll>

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
#define FOE(x, e, b) for(auto x = (ll) e - 1; x != (ll) b; x--)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto& x : C)

using namespace std;

// https://codeforces.com/contest/1611/problem/E2

int main()
{
    ll T;
    cin >> T;
    while(T--)
    {
        ll N, K;
        cin >> N >> K;
        sl rv;
        vl ref(N), bfs0 = { 0 };
        ref[0] = 1;
        vpll bfs1(K);
        FOR(k, K)
        {
            cin >> bfs1[k].first;
            bfs1[k].first--;
            bfs1[k].second = k + 1;
            ref[bfs1[k].first] = -bfs1[k].second;
        }
        vvl graph(N);
        FOR(n, N - 1)
        {
            ll u, v;
            cin >> u >> v;
            u--; v--;
            graph[u].pb(v);
            graph[v].pb(u);
        }
        bool valid = false;
        while(sz(bfs0) && sz(bfs1) && !valid)
        {
            vl tmp0;
            vpll tmp1;
            FORE(v, bfs1)
            {
                FORE(e, graph[v.first])
                {
                    if(ref[e] > -1)
                    { ref[e] = -v.second; tmp1.pb({ e, v.second }); }
                }
            }
            swap(bfs1, tmp1);
            FORE(v, bfs0)
            {
                FORE(e, graph[v])
                {
                    if(!ref[e])
                    {
                        ref[e] = 1;
                        tmp0.pb(e);
                        if(sz(graph[e]) == 1)
                        { valid = true; break; }
                    }
                    elif(ref[e] < 0)
                    { rv.insert(-ref[e]); }
                }
                if(valid)
                { break; }
            }
            swap(bfs0, tmp0);
        }
        if(valid)
        { cout << "-1\n"; }
        else
        { cout << sz(rv) << '\n'; }
    }
}