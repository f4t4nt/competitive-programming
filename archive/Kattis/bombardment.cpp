#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
ll R, n;
ll x[500000];
vector<pii> moves;
ll best[500000];
int main()
{
    cin >> n >> R;
    for (int i=0; i<n; i++)
        cin >> x[i];
    sort(x, x+n);
    queue<pii> q;
    q.push(pii (0, n-1));
    while (!q.empty())
    {
        pii cur=q.front();
        q.pop();
        //cout << "This is current: " << cur.first << " " << cur.second << endl;
        int l=cur.first;
        int r=cur.first;
        while (l<=cur.second)
        {
            while (r<=cur.second && x[r]-x[l]<=2*R)
            {
                r++;
            }
            best[l]=r-l;
            l++;
        }
        int bb=1;
        int curplace=cur.second;
        for (int i=cur.second-1; i>=cur.first; i--)
        {
            if (best[i]>=bb)
            {
                bb=best[i];
                curplace=i;
            }
        }
        //cout << curplace << " " << bb << endl;
        if (curplace>cur.first)
            q.push(pii (cur.first, curplace-1));
        if (curplace+bb-1<cur.second)
            q.push(pii (curplace+bb, cur.second));
        moves.pb(pii (bb, -x[curplace+bb-1]+R));
    }
    
    sort(moves.begin(), moves.end());
    cout << moves.size() << endl;
    for (int i=moves.size()-1; i>0; i--)
        cout << -moves[i].second << " ";
    cout << -moves[0].second << endl;
}