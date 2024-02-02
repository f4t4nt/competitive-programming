#include <iostream>
using namespace std;
typedef long long ll;

ll numones[8];
ll badmask[24];
bool badloc[3][24];
int m, n;
ll dp[8][24];

int main()
{
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<3; j++)
            if (i & (1<<j))
                numones[i]++;
        //cout << numones[i] << " ";
    }
    //cout << endl;
    cin >> m >> n;
    float x, y;
    for (int i=0; i<n; i++)
    {
        cin >> x >> y;
        int f1, f2;
        f1=(int) y;
        f2=(int) x;
        //cout << f1 << " " << f2 << endl;
        badloc[f1][f2]=true;
    }
    for (int i=0; i<m; i++)
        for (int j=0; j<3; j++)
            if (badloc[j][i])
                badmask[i]+=(1<<j);
    for (int j=0; j<m; j++)
    {
        for (int i=0; i<8; i++)
        {
            if (badmask[j] & i)
                continue;
            //if (i==2 || i==4 || i==5 || i==6)
                //continue;
            if (j==0)
            {
                dp[i][j]++;
                if ((i&1) && (i&2))
                    dp[i][j]++;
                if ((i&2) && (i&4))
                    dp[i][j]++;
            }
            else for (int k=0; k<8; k++)
            {
                if (((i | k) & (7^badmask[j-1]))!=(7^badmask[j-1]))
                    continue;
                int potmask=(7^badmask[j-1]) & (7^k);
                //cout << "i and k and potmask: " << i << " " << k << " " << potmask << endl;
                dp[i][j]+=dp[k][j-1];
                //int potmask=(7^badmask[j-1]) & (7^k) & i;
                //dp[i][j]+=dp[k][j-1]*(1<<numones[potmask]);
                if ((i & 1) && (i&2) && ((7^potmask) & 1) && ((7^potmask) & 2))
                {dp[i][j]+=dp[k][j-1];
                    //cout << i << " " << k << endl;
                }
                if ((i & 2) && (i&4) && ((7^potmask) & 2) && ((7^potmask) & 4))
                {dp[i][j]+=dp[k][j-1];
                    //cout << i << " " << k << endl;
                }
            }
        }
    }
    ll ans=0;
    //for (int i=0; i<8; i++)
        //ans+=dp[i][m-1];
    cout << dp[7^badmask[m-1]][m-1] << endl;
    //for (int i=0; i<8; i++)
        //cout << i << " " << dp[i][m-1] << endl;
}