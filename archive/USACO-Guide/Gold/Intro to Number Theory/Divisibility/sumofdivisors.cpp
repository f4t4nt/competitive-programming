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
#define FOI(x, e, i) for(ll x = 0; x < (ll) (e); x += (ll) (i))
#define FORE(x, C) for(auto& x : C)

#define MOD 1000000007

using namespace std;

// https://cses.fi/problemset/task/1082/

void update(ll &rv, ll &n, ll &m, ll &N)
{
    pll tmp = { (n + m - 1) % MOD, (m - n) % MOD };
    if((n % 2 == m % 2 && tmp.first % 2 == 0)
        || (n % 2 != m % 2 && tmp.first % 2 == 1))
    { tmp.first += MOD; }
    if((n % 2 == m % 2 && tmp.second % 2 == 1)
        || (n % 2 != m % 2 && tmp.second % 2 == 0))
    { tmp.second += MOD; }
    if(tmp.first % 2 == 0) { tmp.first /= 2; }
    else { tmp.second /= 2; }
    rv += ((N / n) % MOD * tmp.first % MOD * tmp.second % MOD) % MOD;
    rv %= MOD;
    n = m;
    return;
}

int main()
{
    ll N, n = 1, rv = 0;
    cin >> N;
    while(n <= N)
    {
        ll m = N / (N / n) + 1;
        update(rv, n, m, N);
    }
    cout << rv << endl;
}