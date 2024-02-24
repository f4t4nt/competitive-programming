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
#define MOD 998244353

ll n;

vector<ll> prob[300001];
bool vis[300001];
ll over6[6];

ll poww(ll a, ll b)
{
    ll rv=1;
    while (b) {
        if (b & 1) rv = rv * a % MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return rv;
}

ll inv(ll b)
{
    return poww(b, MOD-2);
}

ll fract(ll a, ll b)
{
    return a*inv(b)%MOD;
}

void dfs(int n)
{
    if (vis[n]) return;
    if (n<=6)
    {
        vis[n]=true;
        prob[n].resize(n+1);
        for (int k=1; k<=n; k++)
        {
            prob[n][k]=fract(1, n);
        }
        return;
    }
    dfs(n-(n/6));
    if (n%6!=0)
    dfs(n-1-(n/6));
    prob[n].resize(n+1);
    ll rem=n%6;
    for (int i=1; i<=n; i++)
    {
        ll irem=(i-1)%6+1;
        if (irem<=rem)
        {
            prob[n][i]=prob[n-1-n/6][i-1-i/6]*over6[irem-1];
            prob[n][i]%=MOD;
            prob[n][i]+=prob[n-1-n/6][i-i/6]*over6[rem-irem];
            prob[n][i]%=MOD;
            prob[n][i]+=prob[n-n/6][i-i/6]*over6[6-rem];
            prob[n][i]%=MOD;
        }
        else if (irem==6)
        {
            if (rem!=0)
            {prob[n][i]=prob[n-1-n/6][i-i/6]*over6[rem];
            prob[n][i]%=MOD;}
            prob[n][i]+=prob[n-n/6][i-i/6]*over6[5-rem];
            prob[n][i]%=MOD;
        }
        else
        {
            if (rem!=0)
            {prob[n][i]=prob[n-1-n/6][i-1-i/6]*over6[rem];
            prob[n][i]%=MOD;}
            prob[n][i]+=prob[n-n/6][i-1-i/6]*over6[irem-1-rem];
            prob[n][i]%=MOD;
            prob[n][i]+=prob[n-n/6][i-i/6]*over6[6-irem];
            prob[n][i]%=MOD;
        }
    }
    vis[n]=true;
    return;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    FOR(i ,6)
    over6[i]=fract(i, 6);
    cin >> n;
    dfs(n);
    for (int i=1; i<=n; i++)
    cout << prob[n][i] << endl;

}