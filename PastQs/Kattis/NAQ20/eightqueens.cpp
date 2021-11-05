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
#define FIND(x, v) find(x.begin(), x.end(), v)
#define FOR(x, e) for(ll  x = 0; x < (ll) (e); x++)
#define FORR(x, e) for(ll x = (ll) (e) - 1; x >= (ll) (0); x--)
#define FOB(x, b, e) for(auto x = (b); x != (e); x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) (e); x += (ll) (i))
#define FORE(x, C) for(auto& x : C)

using namespace std;

// https://open.kattis.com/problems/8queens

bool singles(vl v)
{
    FOR(i, sz(v))
    {
        FOB(j, i + 1, sz(v))
        {
            if(v[i] == v[j])
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    vl x, y, s, d;
    FOR(i, 8)
    {
        FOR(j, 8)
        {
            char c;
            cin >> c;
            if(c == '*')
            {
                x.pb(j);
                y.pb(i);
                s.pb(i + j);
                d.pb(i - j);
            }
        }
    }
    if(singles(x)
        && singles(y)
        && singles(s)
        && singles(d)
        && sz(x) == 8)
    {
        cout << "valid";
    }
    else
    {
        cout << "invalid";
    }
}