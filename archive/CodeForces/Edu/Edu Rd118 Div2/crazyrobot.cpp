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

// https://codeforces.com/contest/1613/problem/E
 
bool valid(ll &n, ll &m, vvl &G)
{
    if(G[n][m] % 2 == 1) { return false; }
    if(G[n][m] == 2) { return true; }
    vl H(4);
    H[G[n + 1][m]]++;
    H[G[n - 1][m]]++;
    H[G[n][m + 1]]++;
    H[G[n][m - 1]]++;
    if(H[2] + H[3] > 0 && H[1] + H[2] + H[3] > 2) { G[n][m] = 3; return true; }
    return false;
}
 
int main()
{
    ll T;
    cin >> T;
    while(T--)
    {
        ll N, M;
        cin >> N >> M;
        N += 2; M += 2;
        qpll bfs;
        vvl G(N, vl(M));
        FOR(n, N) { G[n][0] = 1; G[n][M - 1] = 1; }
        FOR(m, M) { G[0][m] = 1; G[N - 1][m] = 1; }
        FOB(n, 1, N - 1)
        {
            FOB(m, 1, M - 1)
            {
                char g;
                cin >> g;
                if(g == '#') { G[n][m] = 1; }
                elif(g == 'L') { G[n][m] = 2; bfs.push({ n, m }); }
            }
        }
        while(sz(bfs) > 0)
        {
            ll n = bfs.front().first, m = bfs.front().second;
            bfs.pop();
            if(valid(n, m, G))
            {
                if(!G[n + 1][m]) bfs.push({n + 1, m});
                if(!G[n - 1][m]) bfs.push({n - 1, m});
                if(!G[n][m + 1]) bfs.push({n, m + 1});
                if(!G[n][m - 1]) bfs.push({n, m - 1});
            }
        }
        FOB(n, 1, N - 1)
        {
            FOB(m, 1, M - 1)
            {
                if(G[n][m] == 0) { cout << '.'; }
                elif(G[n][m] == 1) { cout << '#'; }
                elif(G[n][m] == 2) { cout << 'L'; }
                elif(G[n][m] == 3) { cout << '+'; }
            }
            cout << '\n';
        }
    }
}