#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

ull binom[100][100];
vector<ull> ans;

void rec(ull prev, ll curmax, ll curd, ll curh)
{
    if (curd==0)
    {
        assert(curh==0);
        ans.push_back(prev);
        return;
    }
    for (ll i=0; i<=curmax; i++)
    {
        if (i*curd<curh)
        {
            continue;
        }
        if (i>curh)
        continue;
        rec(prev*binom[curh][i], i, curd-1, curh-i);
    }
}

int main()
{
    ll d, h;
    cin >> d >> h;
    h--;
    for (ll i=0; i<=h; i++)
    binom[i][0]=1;
    for (ll j=1; j<=h; j++)
    {
        for (ll i=0; i<=h; i++)
        {
            if (i>=j)
            {
                binom[i][j]=binom[i-1][j]+binom[i-1][j-1];
            }
        }
    }
    rec(1, h, d, h);
    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end())-ans.begin());
    for (ll i=0; i<ans.size(); i++)
    {
        cout << ans[i] << endl;
    }
}