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
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)
int n, m;
bool metro[20][50];

map<ll, ll> numones;
map<ll, bool> used;
map<ll, ll> dp;
//map<ll, bool> works;

ll findones(ll x)
{
    ll ans = 0;
    for (ll i=0; i<m; i++)
        if (x & (1LL<<i))
            ans++;
    
    return ans;
}

ll dfs(ll mask)
{
    if (used[mask])
        return dp[mask];
    used[mask]=true;
    numones[mask]=findones(mask);
    if (numones[mask]<=1)
    {
        //works[mask]=true;
        dp[mask]=0;
        return 0;
    }
    dp[mask]=200000000000;
    FOR(j, n)
        {
            ll mask1=0, mask2=0;
            FOR(k, m)
            {
                if (mask & (1LL<<k))
                {
                    if (metro[j][k])
                        mask1+=1LL<<k;
                    else
                        mask2+=1LL<<k;
                }
            }
            if (mask1==mask || mask2==mask)
                continue;
            
            dp[mask]=min(dp[mask], numones[mask]+dfs(mask1)+dfs(mask2));
        }

    //cout << mask << " " << dp[mask] << endl;
    return dp[mask]; 
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    int linesize;
    int station;
    FOR(i, m)
    {
        cin >> linesize;
        FOR(j, linesize)
        {
            cin >> station;
            metro[station][i]=true;
        }
    }

    ll ans=dfs((1LL<<m)-1);
    if (ans>1000)
    {
        cout << "not possible" << endl;
    }
    else
    cout << fixed << setprecision(10) << (ld) ans/m << endl;
}