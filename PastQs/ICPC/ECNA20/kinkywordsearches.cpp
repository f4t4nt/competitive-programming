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
using fl = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())
#define max_elem(C) *max_element(C.begin(), C.end())
#define min_elem(C) *min_element(C.begin(), C.end())
#define contains(C, x) find(C.begin(), C.end(), x) != C.end()

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = (ll) b; x != (ll) e; x++)
#define FOE(x, e, b) for(auto x = (ll) e - 1; x != (ll) b; x--)
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

// https://codeforces.com/gym/324282/problem/B

vector<ll> dx { 0, -1, -1, -1,  0,  1,  1,  1,  0 };
vector<ll> dy { 0, -1,  0,  1,  1,  1,  0, -1, -1 };

int main()
{
    ll r, c, k;
    cin >> r >> c;
    vector<vector<ch>> g(r, vector<ch>(c));
    FOR(x, r) FOR(y, c) cin >> g[x][y];
    cin >> k;
    str s;
    cin >> s;
    if(k < 0 || k > sz(s) - 1)
    { cout << "NO\n"; return 0; }
    // x, y, d, s, k
    vector<vector<vector<vector<vector<bool>>>>> dp(r, 
        vector<vector<vector<vector<bool>>>>(c,
        vector<vector<vector<bool>>>(9,
        vector<vector<bool>>(sz(s),
        vector<bool>(k + 2)))));
    bool valid = false;
    FOR(x, r)
    {
        FOR(y, c)
        {
            if(g[x][y] == s[0])
            {
                dp[x][y][0][0][0] = true;
                if(sz(s) == 1) valid = true;
            }
        }
    }
    FOR(i, k + 1)
    {
        FOR(j0, sz(s))
        {
            FOR(x0, r)
            {
                FOR(y0, c)
                {
                    FOR(d0, 9)
                    {
                        if(!dp[x0][y0][d0][j0][i]) continue;
                        FOB(d1, 1, 9)
                        {
                            if(d0 == d1) continue;
                            ll j1 = j0 + 1,
                                x1 = x0 + dx[d1],
                                y1 = y0 + dy[d1];
                            while(x1 >= 0 &&
                                    x1 < sz(g) &&
                                    y1 >= 0 &&
                                    y1 < sz(g[x1]) &&
                                    j1 < sz(s) &&
                                    g[x1][y1] == s[j1])
                            {
                                dp[x1][y1][d1][j1][i + 1] = true;
                                x1 += dx[d1];
                                y1 += dy[d1];
                                j1++;
                            }
                        }
                    }
                }
            }
        }
    }
    FOR(x, r) FOR(y, c) FOR(i, 9) valid = valid || dp[x][y][i][sz(s) - 1][k + 1];
    if(valid) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}