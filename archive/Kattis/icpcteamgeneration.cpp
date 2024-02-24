#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<int, int> pii;

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

int n;
int a[51];
int b[51];
int dp[51];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i=1; i<=n; i++)
    {
        cin >> a[i] >> b[i];
    }
    for (int i=3; i<=n; i++)
    {
        dp[i]=dp[i-1];
        if (a[i]<=i-2 && b[i-2]>=i)
            dp[i]=max(dp[i], dp[i-3]+1);
    }
    cout << dp[n] << endl;

}