#include <iostream>
#include <vector>
#define MOD 1000000007
using namespace std;

typedef long long ll;
#define pb push_back
vector<ll> pow2;
vector<ll> pow3;
int main()
{
    ll t;
    cin >> t;
    pow2.pb(1);
    pow3.pb(1);
    for (int i=0; i<100000; i++)
    {
        ll num=pow2.back();
        pow2.pb((num*2)%MOD);
        num=pow3.back();
        pow3.pb((num*3)%MOD);
    }
    for (int i=0; i<t; i++)
    {
        ll r, c;
        cin >> r >> c;
        ll ans=pow2[r*c]*pow3[r+c];
        cout << ans%MOD << endl;
    }
}