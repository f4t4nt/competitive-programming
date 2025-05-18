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
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto &x : C)

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

// https://cses.fi/problemset/task/1194/

static const vector<ll> dx { -1, 0, 1, 0};
static const vector<ll> dy { 0, -1, 0, 1};
static const vector<char> dir { 'U', 'L', 'D', 'R' };

int main()
{
    ll n, m;
    cin >> n >> m;
    pair<ll, ll> valid = { -1, -1 }, a0;
    vector<vector<ll>> ref(n, vector<ll>(m, -1));
    vector<vector<ll>> g(n, vector<ll>(m));
    queue<pair<ll, pair<ll, ll>>> bfs;
    FOR(i, n)
    {
        FOR(j, m)
        {
            char c;
            cin >> c;
            if(c == 'A')
            {
                g[i][j] = 1;
                a0 = { i, j };
            }
            elif(c == 'M')
            {
                g[i][j] = 2;
                bfs.push({ 2, { i, j } });
            }
            elif(c == '#') g[i][j] = 3;
        }
    }
    bfs.push({ 1, a0 });
    while(sz(bfs) && valid.first < 0)
    {
        ll t = bfs.front().first,
            x0 = bfs.front().second.first,
            y0 = bfs.front().second.second;
        bfs.pop();
        FOR(i, 4)
        {
            ll x1 = x0 + dx[i], y1 = y0 + dy[i];
            if(x1 < 0 || x1 >= n || y1 < 0 || y1 >= m)
            {
                if(t == 1)
                { valid = { x0, y0 }; break; }
                else continue;
            } 
            if(g[x1][y1]) continue;
            g[x1][y1] = t;
            if(t == 1) ref[x1][y1] = i;
            bfs.push({ t, { x1, y1 } });
        }
    }
    if(valid.first < 0) cout << "NO\n";
    else
    {
        cout << "YES\n";
        str rv = "";
        while(ref[valid.first][valid.second] > -1)
        {
            ll i = ref[valid.first][valid.second];
            rv += dir[i];
            valid.first -= dx[i];
            valid.second -= dy[i];
        }
        flip(rv);
        cout << sz(rv) << '\n';
        cout << rv << '\n';
    }
    return 0;
}