#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<int, int> pii;
typedef pair<int, ld> pid;

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)
#define pb push_back

ll n, k;

ll q[1000001];
ll f[1000001];

bool works(ld x)
{
    set<pid> poss;
    for (int i=1; i<=n; i++)
    {
        if (q[i]!=0)
            poss.insert(pid (f[i], q[i]));
        ld still=x;
        while (!poss.empty() && still>0.0000000001)
        {
            pid y=*poss.begin();
            poss.erase(poss.begin());
            if (y.first<i)
                continue;
            if (y.second>still)
            {
                poss.insert(pid (y.first, y.second-still));
                still=-1;
                break;
            }
            else
            {
                still-=y.second;
            }
        }
        if (still>0.0000000001)
            return false;
    }
    return true;
}

bool evenpossible()
{
    set<pid> poss;
    for (int i=1; i<=n; i++)
    {
        if (q[i]!=0)
            poss.insert(pid (f[i], q[i]));
        while (!poss.empty() && (*poss.begin()).first<i)
        {
            poss.erase(poss.begin());
        }
        if (poss.empty())
            return false;
    }
    return true;
}

ld bs(ld l, ld r)
{
    if (r-l<0.0000000001)
        return l;
    ld mid=(l+r)/2;
    if (works(mid))
        l=mid;
    else
        r=mid;
    return bs(l, r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for (int i=1; i<=n; i++)
    {
        cin >> q[i] >> f[i];
    }
    if (!evenpossible())
    {
        cout << -1 << endl;
        return 0;
    }
    cout << fixed << setprecision(10) << bs(0, 1000000001)/k << endl;

}