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

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)
int n, p;
int degree[100000];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> p;
    int a, b;
    FOR(i, n-1)
    {
        cin >> a >> b;
        degree[a]++;
        degree[b]++;
    }
    int cnt=0;
    FOR(i, n)
    {
        if (degree[i]==1)
            cnt++;
    }
    if (p%cnt==0)
    {
        cout << p/cnt+p/cnt << endl;
    }
    else if (p%cnt==1)
        cout << p/cnt+p/cnt+1 << endl;
    else
        cout << p/cnt+p/cnt+2 << endl;

}