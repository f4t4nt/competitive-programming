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

str dp[101][101][101];
bool works[101][101][101];

int a[100];
int b[100];
int n;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i=0; i<n; i++)
    cin >> a[i];
    for (int i=0; i<n; i++)
    cin >> b[i];

    for (int i=0; i<=n; i++)
    for (int j=0; j<=n; j++)
    works[i][j][0]=true;
    for (int l=1; l<=n; l++)
    {
        for (int f=0; f<n; f++)
        for (int s=0; s+l<=n; s++)
        {
            for (int p=1; p<l; p++)
            {
                if (works[f][s][p] && works[f+p][s+p][l-p])
                {
                    works[f][s][l]=true;
                    dp[f][s][l]=dp[f][s][p]+dp[f+p][s+p][l-p];
                    break;
                }
            }
            if (works[f][s][l])
                continue;
            if (a[f]==b[s+l-1] && works[f+1][s][l-1])
            {
                works[f][s][l]=true;
                dp[f][s][l]="S"+dp[f+1][s][l-1]+"C";
            }
        }
    }
    if (works[0][0][n])
    {
        cout << "YES" << endl << dp[0][0][n] << endl;
    }
    else
        cout << "NO" << endl;

}