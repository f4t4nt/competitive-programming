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
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)
int n;
ll h[100000];
ll h2[100000];
pll best;
bool compare(pll a, pll b)
{
    return a.second*b.first>a.first*b.second;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    FOR(i, n)
    cin >> h[i];
    best=pll (0, 1);
    stack<pll> peaks;
    FOR(i, n)
    {
        while (!peaks.empty() && peaks.top().first<h[i])
            peaks.pop();
        if (!peaks.empty())
        {
            ll tall=peaks.top().first;
            ll pos=peaks.top().second;
            if (pos!=i-1)
            {
                ll tall2=h[pos+1];
                pll newposs=pll (h[i]-tall2+(tall-tall2)*(i-pos-1), tall-tall2);
                if (compare(best, newposs))
                    best=newposs;
            }
        }
        peaks.push(pll (h[i], i));
    }

    while (!peaks.empty())
        peaks.pop();
    
    FOR(i, n)
        h2[i]=h[n-1-i];

    FOR(i, n)
    {
        while (!peaks.empty() && peaks.top().first<h2[i])
            peaks.pop();
        if (!peaks.empty())
        {
            ll tall=peaks.top().first;
            ll pos=peaks.top().second;
            if (pos!=i-1)
            {
                ll tall2=h2[pos+1];
                pll newposs=pll (h2[i]-tall2+(tall-tall2)*(i-pos-1), tall-tall2);
                if (compare(best, newposs))
                    best=newposs;
            }
        }
        peaks.push(pll (h2[i], i));
    }

    for (int i=2; i<=best.second; i++)
    {
        while (best.second%i==0 && best.first%i==0)
        {
            best.second/=i;
            best.first/=i;
        }
    }

    if (best.first!=0)
    {if (best.first%best.second==0)
        cout << best.first/best.second << endl;
    else
        cout << best.first << "/" << best.second << endl;
    }
    else
    cout << 0 << endl;


}