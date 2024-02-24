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
int n;
int a[200000];
int b[200000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i=0; i<n; i++)
    cin >> a[i];
    for (int i=0; i<n; i++)
    cin >> b[i];
    int lcnt=0;
    int pntr=0;
    for (int j=0; j<n; j++)
    {
        if (pntr>=n) break;
        while (pntr<n && a[pntr]<b[j])
            pntr++;
        if (pntr<n)
        {
            lcnt++;
            pntr++;
        }
    }
    int rcnt=0;
    pntr=n-1;
    for (int j=n-1; j>=0; j--)
    {
        if (pntr<0) break;
        while (pntr>=0 && a[pntr]>b[j])
            pntr--;
        if (pntr>=0)
        {
            rcnt++;
            pntr--;
        }
    }
    cout << lcnt-(n-rcnt)+1 << endl;
    for (int k=n-rcnt; k<=lcnt; k++)
        cout << k << " ";
    cout << endl;


}