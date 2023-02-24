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

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

// https://codeforces.com/contest/1647/problem/C

int main()
{
    ll t;
    cin >> t;
    while(t--)
    {
        ll n, m;
        cin >> n >> m;
        bool valid = true;
        vector<vector<bool>> ref(n, vector<bool>(m));
        vector<vector<bool>> g(n, vector<bool>(m));
        FOR(i, n)
        {
            FOR(j, m)
            {
                char c;
                cin >> c;
                if(c == '1') g[i][j] = true;
            }
        }
        if(g[0][0]) cout << -1 << '\n';
        else
        {
            vector<vector<ll>> rv;
            queue<pair<ll, ll>> bfs;
            bfs.push({n - 1, m - 1});
            while(sz(bfs))
            {
                pair<ll, ll> p;
                p = bfs.front();
                bfs.pop();
                if(g[p.first][p.second])
                {
                    if(p.first > 0) rv.pb({ p.first - 1, p.second, p.first, p.second });
                    else rv.pb({ p.first, p.second - 1, p.first, p.second });
                }
                if(p.first > 0 && !ref[p.first - 1][p.second])
                { bfs.push({ p.first - 1, p.second }); ref[p.first - 1][p.second] = true; }
                if(p.second > 0 && !ref[p.first][p.second - 1])
                { bfs.push({ p.first, p.second - 1 }); ref[p.first][p.second - 1] = true; }
            }
            cout << sz(rv) << '\n';
            FOR(i, sz(rv)) cout << rv[i][0] + 1 << ' ' << rv[i][1] + 1 << ' ' << rv[i][2] + 1 << ' ' << rv[i][3] + 1 << '\n';
        }
    }
    return 0;
}