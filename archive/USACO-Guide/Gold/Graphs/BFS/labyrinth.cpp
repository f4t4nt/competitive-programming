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
#define vvvvl vector<vvvl>
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
#define ssort(x) sort(x.begin(), x.end())
#define rsort(x) sort(x.begin(), x.end(), greater<>())

#define FOR(x, e) for(ll  x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= (ll) 0; x--)
#define FOB(x, b, e) for(auto x = (ll) b; x != (ll) e; x++)
#define FOE(x, e, b) for(auto x = (ll) e - 1; x >= (ll) b; x--)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FORE(x, C) for(auto& x : C)

using namespace std;

// https://cses.fi/problemset/task/1193/

static const vl dx { -1, 0, 1, 0};
static const vl dy { 0, -1, 0, 1};

int main()
{
	ll N, M, ax, ay, bx, by;
	cin >> N >> M;
	vvl G(N, vl(M));
	FOR(n, N)
	{
		FOR(m, M)
		{
			char c;
			cin >> c;
			if(c == '#')
			{ G[n][m] = 1; }
			elif(c == '.')
			{ G[n][m] = 0; }
			elif(c == 'A')
			{ G[n][m] = 2; ax = n; ay = m; }
			elif(c == 'B')
			{ G[n][m] = 3; bx = n; by = m; }
		}
	}
	qpll bfs;
    vvl ref(N, vl(M, -1));
	bfs.push({ ax, ay });
	while(sz(bfs))
	{
		ll x = bfs.front().first, y = bfs.front().second;
		bfs.pop();
		if(G[x][y] == 1)
		{ continue; }
		if(x == bx && y == by)
		{ break; }
        FOR(i, 4)
        {
            ll nx = x + dx[i],  ny = y + dy[i];
            if(nx >= 0 && nx < N && ny >= 0 && ny < M && ref[nx][ny] == -1)
            { bfs.push({ nx, ny }); ref[nx][ny] = i; }
        }
	}
	if(ref[bx][by] != -1)
	{
        cout << "YES\n";
        str rv, dir = "ULDR";
        while(ax != bx || ay != by)
        { ll &d = ref[bx][by]; rv += dir[d]; bx -= dx[d]; by -= dy[d]; }
        reverse(rv.begin(), rv.end());
        cout << sz(rv) << '\n' << rv << '\n';
    }
	else
	{ cout << "NO" << '\n'; }
}