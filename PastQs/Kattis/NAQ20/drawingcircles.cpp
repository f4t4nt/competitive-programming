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

#define pi 3.1415926535

using namespace std;

// https://naq20.kattis.com/problems/drawingcircles

struct circ
{
    double x;
    double y;
    double r;
    set<pair<double, double>> S = { { 0.0, 2.0 * pi } };
};

double dist2(circ &c1, circ &c2)
{ return (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y); }

bool contactless(circ &c1, circ &c2)
{ return (c1.r + c2.r) <= sqrt(dist2(c1, c2)); }

bool eclipse(circ &c1, circ &c2)
{ return (c1.r - c2.r) >= sqrt(dist2(c1, c2)); }

void insertArc(double theta1, double theta2, set<pair<double, double>> &S)
{
    set<pair<double, double>> rv;
    FORE(s, S)
    {
        if(s.first >= theta2 || s.second <= theta1) { rv.insert(s); }
        elif(s.first >= theta1 && s.second <= theta2) { continue; }
        else
        {
            if(s.first <= theta1 && s.second >= theta1) { rv.insert({ s.first, theta1 }); }
            if(s.first <= theta2 && s.second >= theta2) { rv.insert({ theta2, s.second}); }
        }
    }
    S = rv;
}

void updateArc(circ &c1, circ &c2)
{
    double &x1 = c1.x,
        &x2 = c2.x,
        &y1 = c1.y,
        &y2 = c2.y,
        &r1 = c1.r,
        &r2 = c2.r,
        R2 = dist2(c1, c2),
        xi1 = (x1 + x2) / 2 + (r1 * r1 - r2 * r2) / (2 * R2) * (x2 - x1) + 0.5 * sqrt(2 * (r1 * r1 + r2 * r2) / R2 - (r1 * r1 - r2 * r2) * (r1 * r1 - r2 * r2) / (R2 * R2) - 1) * (y2 - y1),
        xi2 = (x1 + x2) / 2 + (r1 * r1 - r2 * r2) / (2 * R2) * (x2 - x1) - 0.5 * sqrt(2 * (r1 * r1 + r2 * r2) / R2 - (r1 * r1 - r2 * r2) * (r1 * r1 - r2 * r2) / (R2 * R2) - 1) * (y2 - y1),
        yi1 = (y1 + y2) / 2 + (r1 * r1 - r2 * r2) / (2 * R2) * (y2 - y1) + 0.5 * sqrt(2 * (r1 * r1 + r2 * r2) / R2 - (r1 * r1 - r2 * r2) * (r1 * r1 - r2 * r2) / (R2 * R2) - 1) * (x1 - x2),
        yi2 = (y1 + y2) / 2 + (r1 * r1 - r2 * r2) / (2 * R2) * (y2 - y1) - 0.5 * sqrt(2 * (r1 * r1 + r2 * r2) / R2 - (r1 * r1 - r2 * r2) * (r1 * r1 - r2 * r2) / (R2 * R2) - 1) * (x1 - x2),
        theta1 = atan2(yi2 - y2, xi2 - x2),
        theta2 = atan2(yi1 - y2, xi1 - x2);
    if(theta1 < 0) { theta1 += 2 * pi; }
    if(theta2 < 0) { theta2 += 2 * pi; }
    
    if(theta2 < theta1) { insertArc(-1, theta2, c2.S); insertArc(theta1, 2 * pi + 1, c2.S); }
    else { insertArc(theta1, theta2, c2.S); }
}

double visible(circ &c)
{
    double rv = 0;
    FORE(s, c.S) { rv += c.r * (s.second - s.first); }
    return rv;
}

int main()
{
    ll N;
    cin >> N;
    vector<circ> C(N);
    FOR(n, N)
    {
        cin >> C[n].x >> C[n].y >> C[n].r;
        FOR(m, n)
        {
            if(eclipse(C[n], C[m])) { C[m].S = {}; }
            elif(sz(C[m].S) == 0 || contactless(C[n], C[m]) || eclipse(C[m], C[n])) { continue; }
            else { updateArc(C[n], C[m]); }
        }

    }
    double rv = 0;
    FOR(n, N) { rv += visible(C[n]); }
    cout.precision(18);
    cout << rv << endl;
}