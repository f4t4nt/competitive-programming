#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef string str;
typedef char ch;
typedef long double ld;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define fliip(C) reverse(all(C))
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

struct point
{
    ll x, y;
};

ll area(point a, point b, point c)
{
    ll ans=(a.x*b.y+b.x*c.y+c.x*a.y-a.y*b.x-b.y*c.x-c.y*a.x);
    if (ans<0)
        return -ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t;
    cin >> t;
    ll x1, y1, x2, y2, x3, y3, px, py;
    cout << fixed << setprecision(10);
    FOR(i, t)
    {
        //cout << "hi" << endl;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> px >> py;
        point p[3];
        point pt;
        pt.x=px; pt.y=py;
        p[0].x=x1; p[0].y=y1; p[1].x=x2; p[1].y=y2; p[2].x=x3; p[2].y=y3;
        ll a[3];
        ll at;
        at=area(p[0], p[1], p[2]);
        a[0]=area(p[1], p[2], pt);
        a[1]=area(p[0], p[2], pt);
        a[2]=area(p[0], p[1], pt);
        //cout << at << " " << a[0] << " " << a[1] << " " << a[2] << '\n';
        if (a[0]+a[1]+a[2]!=at)
        {
            cout << -1 << '\n';
            continue;
        }
        if (a[0]!=0 && a[1]!=0 && a[2]!=0)
        {
            cout << -1 << '\n';
            continue;
        }
        int corner=-1;
        FOR (j, 3)
        {
            if (a[j]==at)
                corner=j;
        }
        if (corner!=-1)
        {
            int A=(corner+1)%3;
            int B=(corner+2)%3;
            cout << ((ld) p[A].x+p[B].x)/2 << " " << ((ld) p[A].y+p[B].y)/2 << '\n';
            continue;
        }
        int B=0;
        FOR(j, 3)
        {
            if (a[j]==0)
            {
                B=j;
            }
        }
        int A=B;
        FOR (j, 3)
        {
            if (a[j]>0 && 2*a[j]<at)
            {
                A=j;
            }
        }
        if (A==B)
        {
            cout << p[B].x << " " << p[B].y << '\n';
            continue;
        }
        int C=3-A-B;
        ll denom=2*(pt.x-p[A].x);
        ll numer=p[C].x-p[A].x;
        if (denom==0)
        {
            denom=2*(pt.y-p[A].y);
            numer=p[C].y-p[A].y;
        }
        if (denom<0)
        {
            denom=-denom;
            numer=-numer;
        }
        cout << p[A].x +(ld) numer/(ld) denom*(p[B].x-p[A].x) << " " << p[A].y + (ld) numer/(ld) denom*(p[B].y-p[A].y) << '\n';
    }
}