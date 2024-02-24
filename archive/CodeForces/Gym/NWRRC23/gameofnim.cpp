#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<ll, ll> pll;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define ssort(C) sort(all(C))

int n, p, m;
int dp[500][500][512];
bool vis[500][500][512];

int dfs(int k, int t, int l)
{
    if (k==0)
        vis[k][t][l]=true;
    if (vis[k][t][l])
        return dp[k][t][l];
    vis[k][t][l]=true;
    for (int numpiles=0; numpiles*k<=t; numpiles++)
    {
        int mod2=(numpiles%2)*k;
        int rem=numpiles*k;
        dp[k][t][l]+=dfs(k-1,t-rem,l^mod2);
        dp[k][t][l]%=m;
    }
    return dp[k][t][l];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> p >> m;
    dp[0][0][0]=1;
    vis[0][0][0]=true;
    /*for (int k=1; k<=n-p; k++)
    {
        for (int t=0; t<=n-p; t++)
        {
            for (int l=0; l<512; l++)
            {
                for (int numpiles=0; numpiles*k<=t; numpiles++)
                {
                    int mod2=(numpiles%2)*k;
                    int rem=numpiles*k;
                    dp[k][t][l]+=dp[k-1][t-rem][l^mod2];
                    dp[k][t][l]%=m;
                }
                //cout << k << " " << t << " " << l << " " << dp[k][t][l] << endl;
            }
        }
    }*/
    cout << dfs(n-p, n-p, p) << endl;

}
