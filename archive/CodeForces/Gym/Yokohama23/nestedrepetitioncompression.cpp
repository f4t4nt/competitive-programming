#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)
string s;
int n;

int rep[201][201];
string dp[201][201];
string makestr(int x)
{
    string ans;
    while (x>0)
    {
        ans=" "+ans;
        ans[0]=(char) ((x%10)+(int) '0');
        x/=10;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> s;
    n=s.length();
    for (int i=0; i<=n; i++)
    for (int j=i+1; j<=n; j++)
    rep[i][j]=1;
    for (int i=0; i<n; i++)
    for (int j=1; j<=n-i; j++)
    {
        string cur=s.substr(i, j);
        int cnt=1;
        while (cnt*j+j+i<=n && cur==s.substr(i+cnt*j, j))
        {
            rep[i][i+cnt*j+j]=max(rep[i][i+cnt*j+j], cnt+1);
            cnt++;
        }
        //cout << i << " " << i+j << " " << rep[i][i+j] << endl;
    }

    for (int l=1; l<=n; l++)
    for (int i=0; i+l<=n; i++)
    {
        dp[i][i+l]=s.substr(i, l);
        if (l>1)
        {
            for (int k=1; k<l; k++)
            {
                if (dp[i][i+k].size()+dp[i+k][i+l].size()<dp[i][i+l].size())
                {
                    dp[i][i+l]=dp[i][i+k]+dp[i+k][i+l];
                }
            }
            int numreps=rep[i][i+l];
            for (int k=2; k<=9; k++)
            {
                if (numreps%k!=0) continue;
                string poss=makestr(k)+"("+dp[i][i+l/k]+")";
                if (poss.size()<dp[i][i+l].size())
                    dp[i][i+l]=poss;
            }
        }

        //cout << i << " " << i+l << " " << dp[i][i+l] << endl;
    }

    cout << dp[0][n] << endl;



}