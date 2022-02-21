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
#define last_elem(coll) (*(coll.rbegin()))
#define FIND(x, v) find(x.begin(), x.end(), v)
#define FOR(x, e) for(ll  x = 0; x < (ll) (e); x++)
#define FORR(x, e) for(ll x = (ll) (e) - 1; x >= (ll) (0); x--)
#define FOB(x, b, e) for(auto x = (b); x != (e); x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) (e); x += (ll) (i))
#define FORE(x, C) for(auto& x : C)

using namespace std;

// https://open.kattis.com/problems/cantinaofbabel

ll lang2idx(mstrl &langs, str &tmp)
{
    if(langs[tmp] == 0) { langs[tmp] = sz(langs); }
    return langs[tmp];
}

int main()
{
    ll N, rv = 0;
    cin >> N;
    mstrl langs;
    vplsl P(N);
    vsl pairs(N), group(N);
    str line, tmp;
    getline(cin, line);
    FORE(p, P)
    {
        getline(cin, line);
        stringstream ss(line);
        ss >> tmp >> tmp;
        p.first = lang2idx(langs, tmp);
        p.second.insert(p.first);
        while(!ss.eof())
        {
            ss >> tmp;
            p.second.insert(lang2idx(langs, tmp));
        }
    }
    FOR(n, N)
    {
        FOR(m, N)
        {
            if(P[m].second.find(P[n].first) != P[m].second.end()) { pairs[n].insert(m); }
        }
    }
    FOR(n, N)
    {
        FOR(i, N)
        {
            FORE(j, pairs[i])
            {
                FORE(k, pairs[j])
                {
                    pairs[i].insert(k);
                }
            }
        }
    }
    FOR(n, N)
    {
        FOR(m, N)
        {
            if(pairs[n].find(m) != pairs[n].end() &&
                pairs[m].find(n) != pairs[m].end())
            {
                group[n].insert(m);
                group[m].insert(n);
            }
        }
    }
    FOR(n, N) { rv = max(rv, sz(group[n])); }
    cout << N - rv << endl;
}