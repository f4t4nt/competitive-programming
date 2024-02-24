#include <bits/stdc++.h>

using namespace std;

typedef int ll;
typedef double ld;
typedef char ch;
typedef string str;
typedef pair<int, int> pll;
typedef pair<ld, ld> pld;
typedef pair<ld, pll> pdl;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)
int h, w;
char grid[700][700];

map<pll, vector<pdl> > adj;

map<pll, ld> dist;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> h >> w;
    for (int i=0; i<h; i++)
    for (int j=0; j<w; j++)
    cin >> grid[i][j];
    for (int i=0; i<=2*h; i++)
    for (int j=0; j<=2*w; j++)
    {
        if (i%2==1 && j%2==1) continue;
        if (i%2==0 && j%2==0) continue;
        dist[pll (i, j)]=1000000000;
        if (i%2==0)
        {
            if (j>2)
                adj[pll (i, j)].pb(pdl(10, pll (i, j-2)));
            if (j<2*w-2)
                adj[pll (i, j)].pb(pdl(10, pll (i, j+2)));
        }
        if (j%2==0)
        {
            if (i>2)
                adj[pll (i, j)].pb(pdl (10, pll (i-2, j)));
            if (i<2*h-2)
                adj[pll (i, j)].pb(pdl (10, pll (i+2, j)));
        }
        if (i%2==0 && j%2==1 && i/2<h)
        {
            if (grid[i/2][j/2]=='O') {
            adj[pll (i, j)].pb(pdl (3.141592653589793*2.5, pll(i+1, j-1)));
            adj[pll (i, j)].pb(pdl(3.141592653589793*2.5, pll (i+1, j+1)));
            adj[pll (i+1, j-1)].pb(pdl(3.141592653589793*2.5, pll (i, j)));
            adj[pll (i+1, j+1)].pb(pdl(3.141592653589793*2.5, pll (i, j)));
            }

            else
            {
                adj[pll (i, j)].pb(pdl (10, pll(i+1, j-1)));
            adj[pll (i, j)].pb(pdl(10, pll (i+1, j+1)));
            adj[pll (i+1, j-1)].pb(pdl(10, pll (i, j)));
            adj[pll (i+1, j+1)].pb(pdl(10, pll (i, j)));
            }
        }
        if (i%2==0 && j%2==1 && i/2>0)
        {
            if (grid[i/2-1][j/2]=='O')
            {
adj[pll (i, j)].pb(pdl(3.141592653589793*2.5, pll(i-1, j+1)));
            adj[pll (i, j)].pb(pdl(3.141592653589793*2.5, pll (i-1, j-1)));
            adj[pll (i-1, j+1)].pb(pdl(3.141592653589793*2.5, pll (i, j)));
            adj[pll (i-1, j-1)].pb(pdl(3.141592653589793*2.5, pll (i, j)));
            }
            else
            {
                adj[pll (i, j)].pb(pdl (10, pll(i-1, j-1)));
            adj[pll (i, j)].pb(pdl(10, pll (i-1, j+1)));
            adj[pll (i-1, j-1)].pb(pdl(10, pll (i, j)));
            adj[pll (i-1, j+1)].pb(pdl(10, pll (i, j)));
            }
            
        }
    }
    dist[pll (0, 1)]=5;
    dist[pll (1, 0)]=5;
    for (int i=0; i<=2*h; i++)
    for (int j=0; j<=2*w; j++)
    {
        if (i%2==j%2) continue;
        pll x=pll (i, j);
        for (int i=0; i<adj[x].size(); i++)
        {
            dist[adj[x][i].second]=min(dist[adj[x][i].second], dist[x]+adj[x][i].first);
        }
    }
    cout << fixed << setprecision(10) << min(dist[pll (2*h-1, 2*w)], dist[pll (2*h, 2*w-1)])+5 << endl;


    return 0;
}