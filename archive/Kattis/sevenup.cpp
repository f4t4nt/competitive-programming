#include <iostream>
#include <cstring>
#include <queue>
#include <cassert>
#include <iomanip>
using namespace std;
typedef long double ld;

ld dp[60][128];

int numhave[7];
bool ifneeded[7];
bool leafstart[7];
int whichcpnt[7];
bool vis[7];

int dir[7];

int main()
{
    memset(dir, -1, sizeof(dir));
    string s;
    cin >> s;
    for (int j=0; j<7; j++)
        numhave[j]=4;
    for (int j=0; j<7; j++)
    {
        if ((int) '2'<= (int) s[j] && (int) s[j]<=(int) '7')
        {
            numhave[(int) s[j]-(int) '2'+1]--;
            dir[j]=(int) s[j]-(int) '2'+1;
        }
        else if (s[j]=='A')
        {
            numhave[0]--;
            dir[j]=0;
        }
    }
    //create ifneeded, bitmask considerations, etc.
    memset(leafstart, true, sizeof(leafstart));
    memset(whichcpnt, -1, sizeof(whichcpnt));
    for (int j=0; j<7; j++)
        if (dir[j]!=-1)
            leafstart[dir[j]]=false;
    for (int j=0; j<7; j++)
        if (leafstart[j])
        {
            //cout << "Hi" << " " << j << endl;
            ifneeded[j]=true;
            whichcpnt[j]=j;
            vis[j]=true;
            queue<int> bfs;
            bfs.push(j);
            while (!bfs.empty())
            {
                int top=bfs.front();
                bfs.pop();
                if (dir[top]!=-1 && !vis[dir[top]])
                {
                    vis[dir[top]]=true;
                    bfs.push(dir[top]);
                }
            }
        }
    
    for (int j=0; j<7; j++)
    {
        if (!vis[j])
        {
            ifneeded[j]=true;
            queue<int> bfs;
            bfs.push(j);
            while (!bfs.empty())
            {
                int top=bfs.front();
                vis[top]=true;
                bfs.pop();
                whichcpnt[top]=j;
                assert(dir[top]!=-1);
                if (!vis[dir[top]])
                    bfs.push(dir[top]);
            }
        }
    }
    
    /*for (int j=0; j<7; j++)
    {
        cout << dir[j] << " " << ifneeded[j] << " " << whichcpnt[j] << " " << numhave[j] << endl;    }*/
    dp[0][0]=1;
    for (int i=0; i<45; i++)
    {
        for (int j=0; j<128; j++)
        {
            int totalnum=0;
            for (int k=0; k<7; k++)
            {
                if (whichcpnt[k]==-1)
                    continue;
                if (ifneeded[whichcpnt[k]] && ((j & (1<<whichcpnt[k])) ==0))
                {
                    totalnum+=numhave[k];
                    dp[i+1][j+(1<<whichcpnt[k])]+=dp[i][j]*(numhave[k])/(45-i);
                }
            }
            dp[i+1][j]+=dp[i][j]*(45-i-totalnum)/(45-i);
        }
    }
    ld ans=0;
    int finalmask=0;
    for (int j=0; j<7; j++)
        if (ifneeded[j])
            finalmask+=(1<<j);
    ans+=dp[0][finalmask];
    for (int i=1; i<=45; i++)
        ans+=(dp[i][finalmask]-dp[i-1][finalmask])*i;
    cout << fixed << setprecision(10) << ans << endl;
}