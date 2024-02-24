#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<int, int> pii;

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

int school[100001];
int adv[100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int k, n, c;
    cin >> n >> k >> c;
    queue<pii> ids;
    int t, s;
    int cnt=0;
    for (int i=0; i<n; i++)
    {
        cin >> t >> s;
        if (school[s]<c)
        {
            cnt++;
            school[s]++;
            adv[i]=t;
        }
        else
        {
            ids.push(pii (i, t));
        }
        if (cnt==k) break;
    }
    while (cnt<k)
    {
        adv[ids.front().first]=ids.front().second;
        ids.pop();
        cnt++;
    }

    for (int i=0; i<n; i++)
    {
        if (adv[i]!=0)
            cout << adv[i] << endl;
    }

}