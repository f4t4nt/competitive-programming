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

using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using ull = unsigned long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using vvvvl = vector<vvvl>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvpll = vector<vpll>;
using plvpll = pair<ll, vpll>;
using plvl = pair<ll, vl>;
using vplvl = vector<plvl>;
using sl = set<ll>;
using spll = set<pll>;
using vsl = vector<sl>;
using ssl = set<sl>;
using plsl = pair<ll, sl>;
using vplsl = vector<plsl>;
using plspll = pair<ll, spll>;
using msl = multiset<ll>;
using mspll = multiset<pll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using plvb = pair<ll, vb>;
using mll = map<ll, ll>;
using mlll = map<ll, mll>;
using mlvl = map<ll, vl>;
using mlpll = map<ll, pll>;
using mplll = map<pll, ll>;
using mlvpll = map<ll, vpll>;
using mlsl = map<ll, sl>;
using mpllb = map<pll, bool>;
using vmll = vector<mll>;
using ql = queue<ll>;
using qpll = queue<pll>;
using fl = long double;
using vf = vector<fl>;
using vvf = vector<vf>;
using str = string;
using vstr = vector<str>;
using mstrl = map<str, ll>;
using mcl = map<char, ll>;

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

// https://codeforces.com/contest/1627/problem/B

int main()
{
    ll T;
    cin >> T;
    while(T--)
    {
        ll N, M;
        cin >> N >> M;
        vvl G(N, vl(M));
        ll s = N / 2 + M / 2;
        qpll bfs;
        vl rv;
        if(N % 2 && M % 2)
        {
            G[N / 2][M / 2] = s;
            bfs.push({ N / 2, M / 2 });
        }
        else if(N % 2 && !(M % 2))
        {
            G[N / 2][M / 2] = s;
            G[N / 2][M / 2 - 1] = s;
            bfs.push({ N / 2, M / 2 });
            bfs.push({ N / 2, M / 2 - 1 });
        }
        else if(!(N % 2) && M % 2)
        {
            G[N / 2][M / 2] = s;
            G[N / 2 - 1][M / 2] = s;
            bfs.push({ N / 2, M / 2 });
            bfs.push({ N / 2 - 1, M / 2 });
        }
        else if(!(N % 2) && !(M % 2))
        {
            G[N / 2][M / 2] = s;
            G[N / 2][M / 2 - 1] = s;
            G[N / 2 - 1][M / 2] = s;
            G[N / 2 - 1][M / 2 - 1] = s;
            bfs.push({ N / 2, M / 2 });
            bfs.push({ N / 2, M / 2 - 1 });
            bfs.push({ N / 2 - 1, M / 2 });
            bfs.push({ N / 2 - 1, M / 2 - 1 });
        }
        while(sz(bfs))
        {
            pll xy = bfs.front();
            bfs.pop();
            rv.pb(G[xy.first][xy.second]);
            for(int dx = -1; dx <= 1; dx++)
            {
                for(int dy = -1; dy <= 1; dy++)
                {
                    if(dx && dy)
                    { continue; }
                    if(dx == dy)
                    { continue; }
                    ll x = xy.first + dx, y = xy.second + dy;
                    if(x >= 0 && x < N && y >= 0 && y < M && !G[x][y])
                    {
                        G[x][y] = G[xy.first][xy.second] + 1;
                        bfs.push({ x, y});
                    }
                }
            }
        }
        FORE(r, rv)
        { cout << r << ' '; }
        cout << '\n';
    }
    return 0;
}