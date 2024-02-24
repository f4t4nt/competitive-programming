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
ll n, c, p, q;
ll total[500001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> c >> p >> q;
    char x;
    FOR(i, n)
    {
        cin >> x;
        if (x=='Y')
            total[i+1]=total[i]+1;
        else
            total[i+1]=total[i];
    }
    ll rk=0;
    ll prevpos=0;
    for (int i=1; i<=n; i++)
    {
        if (i-prevpos<c) continue;
        for (int j=i-c; j>max(i-2*c, prevpos-1); j--)
        {
            if ((total[i]-total[j])*q>=(i-j)*p)
            {
                rk++;
                prevpos=i;
                //cout << rk << " " << prevpos << endl;
                break;
            }
        }
    }
    cout << rk << endl;

}
