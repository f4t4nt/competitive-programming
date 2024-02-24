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

int nz(ll b, ll n)
{
    int ans=0;
    while (n>0)
    {
        if (n%b==0)
            ans++;
        n/=b;
    }
    return ans;
}
int t;

//int numzero[1000000];
vector<ll> whichones[100];

map<ll, ll> cube;

map<ll, vector<ll> > prevans;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    /*for (ll i=0; i<=60; i++)
        for (ll j=0; j<i-1; j++)
        {
            ll best=1;
            ll cur=(1LL<<i)-1-(1LL<<j);
            bool flag=false;
            for (ll k=3; k*k<=cur; k++)
            {
                if (nz(k, cur)>=2)
                {
                    //cout << k << " " << i << " " <<j << " " << cur << " " << nz(k, cur) << endl;
                    flag=true;
                    break;
                }
            }
            if (!flag)
                cout << cur << " " << i << " " << j << endl;
        }
    for (ll i=0; i<=60; i++)
        for (ll j=0; j<i-1; j++)
            for (ll k=0; k<j; k++)
            {
                ll best=2;
                ll cur=(1LL<<i)-1-(1LL<<j)-(1LL<<k);
                bool flag=false;
                for (ll k=3; k*k*k<=cur; k++)
                {
                    if (nz(k, cur)>=3)
                    {
                        //cout << k << " " << i << " " <<j << " " << cur << " " << nz(k, cur) << endl;
                        flag=true;
                        break;
                    }
                }
                if (!flag)
                    cout << cur << " " << i << " " << j << " " << k << endl;
            }*/
    for (ll i=1; i<=1000000; i++)
        cube[i*i*i]=i;
    cin >> t;
    for (int attempt=0; attempt<t; attempt++)
    {
        ll n;
        cin >> n;
        if (prevans.find(n)!=prevans.end())
        {
            cout << prevans[n][0] << " " << prevans[n][1] << endl;
            for (int j=2; j<prevans[n].size(); j++)
                cout << prevans[n][j] << " ";
            cout << endl;
            continue;
        }
        for (int j=0; j<100; j++)
            whichones[j].clear();
        int best=1;
        ll base=2;
        while (base*base*base*base<=n)
        {
            int numzero=nz(base, n);
            whichones[numzero].pb(base);
            best=max(best, numzero);
            base++;
        }
        if (best>=4)
        {
                        sort(all(whichones[best]));
            prevans[n].pb(best); prevans[n].pb(whichones[best].size());
            for (int j=0; j<whichones[best].size(); j++)
                prevans[n].pb(whichones[best][j]);
            cout << prevans[n][0] << " " << prevans[n][1] << endl;
            for (int j=2; j<prevans[n].size(); j++)
                cout << prevans[n][j] << " ";
            cout << endl;
            continue;
        }
        if (best==3)
        {
            for (ll j=1; j*j*j*j<n; j++)
            {
                if (n%j!=0) continue;
                if (cube.find(n/j)!=cube.end())
                    {
                        whichones[3].pb(cube[n/j]);
                    }
            }
                        sort(all(whichones[best]));
            prevans[n].pb(best); prevans[n].pb(whichones[best].size());
            for (int j=0; j<whichones[best].size(); j++)
                prevans[n].pb(whichones[best][j]);
            cout << prevans[n][0] << " " << prevans[n][1] << endl;
            for (int j=2; j<prevans[n].size(); j++)
                cout << prevans[n][j] << " ";
            cout << endl;
            continue;
        }
        if (best==2)
        {
            while (base*base<=n)
            {
                int numzero=nz(base, n);
                whichones[numzero].pb(base);
                best=max(best, numzero);
                base++;
            }
                        sort(all(whichones[best]));
            prevans[n].pb(best); prevans[n].pb(whichones[best].size());
            for (int j=0; j<whichones[best].size(); j++)
                prevans[n].pb(whichones[best][j]);
            cout << prevans[n][0] << " " << prevans[n][1] << endl;
            for (int j=2; j<prevans[n].size(); j++)
                cout << prevans[n][j] << " ";
            cout << endl;
            continue;

        }
        if (best==1)
        {
            while (base*base<=n)
            {
                int numzero=nz(base, n);
                whichones[numzero].pb(base);
                best=max(best, numzero);
                base++;
            }
            for (ll k=1; k*k<n; k++)
            {
                if (n%k==0)
                    whichones[1].pb(n/k);
            }
            sort(all(whichones[best]));
            whichones[best].resize(unique(whichones[best].begin(), whichones[best].end())-whichones[best].begin());
            prevans[n].pb(best); prevans[n].pb(whichones[best].size());
            for (int j=0; j<whichones[best].size(); j++)
                prevans[n].pb(whichones[best][j]);
            cout << prevans[n][0] << " " << prevans[n][1] << endl;
            for (int j=2; j<prevans[n].size(); j++)
                cout << prevans[n][j] << " ";
            cout << endl;
            continue;
        }
    }
    
}