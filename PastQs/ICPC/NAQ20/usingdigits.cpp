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
#define str string
#define vstr vector<str>
#define pb push_back
#define elif else if

#define sz(x) (ll) x.size()
#define vsort(x) sort(x.begin(), x.end())
#define last_elem(coll) (*(coll.rbegin()))
#define FOR(x, e) for(ll  x = 0; x < (ll) (e); x++)
#define FORR(x, e) for(ll x = (ll) (e) - 1; x >= (ll) (0); x--)
#define FOB(x, b, e) for(auto x = (b); x != (e); x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) (e); x += (ll) (i))
#define FORE(x, C) for(auto& x : C)

using namespace std;

// https://open.kattis.com/problems/usingdigits

int main()
{
    ll X, Y;
    cin >> X >> Y;
    str Ks;
    cin >> Ks;
    vl K;
    FOR(i, sz(Ks)) { K.pb(Ks[i] - '0'); }
    K.pb(0);
    K.pb(0);
    vstr Gs(Y);
    vvl G(Y, vl(X));
    FOR(y, Y) { cin >> Gs[y]; }
    FOR(y, Y) { FOR(x, X) { G[y][x] = Gs[Y - y - 1][x] - '0'; } }
    vvvl GK = vvvl(Y + 10, vvl(X + 10, vl(sz(K), LLONG_MAX)));

    FOR(k, sz(K)) { GK[Y - 1][X - 1][k] = G[Y - 1][X - 1]; }

    FORR(y, Y)
    {
        FORR(x, X)
        {
            if(x + 1 == X && y + 1 == Y) { continue; }

            FOR(k, sz(K) - 1)
            {
                ll d = K[k];
                GK[y][x][k] = G[y][x] + min({
                    GK[y][x + d + 1][k + 1],
                    GK[y + d + 1][x][k + 1],
                    GK[y][x + 1][k],
                    GK[y + 1][x][k]
                });
            }
        }
    }

    cout << GK[0][0][0] << endl;
}