#include <iostream>
using namespace std;
typedef long long ll;

char grid[14][14];
ll dp[14][14][10];
int n, m;
ll ans;
string s="YOKOHAMA";
int main()
{
    cin >> n >> m;
    for (int i=1; i<=n; i++)
    for (int j=1; j<=m; j++)
    {
        cin >> grid[i][j];
        if (grid[i][j]==s[0])
        dp[i][j][0]=1;
    }
    for (int k=1; k<8; k++)
    for (int i=1; i<=n; i++)
    for (int j=1; j<=m; j++)
    {
        if (grid[i][j]!=s[k])
            continue;
        dp[i][j][k]+=dp[i-1][j][k-1];
        dp[i][j][k]+=dp[i+1][j][k-1];
        dp[i][j][k]+=dp[i][j-1][k-1];
        dp[i][j][k]+=dp[i][j+1][k-1];
        //cout << i << j << k << " " << dp[i][j][k] << endl;
    }
    for (int i=1; i<=n; i++)
    for (int j=1; j<=m; j++)
    ans+=dp[i][j][7];
    cout << ans << endl;
}