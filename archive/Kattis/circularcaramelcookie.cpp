#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
ll n;
bool findmin(ll r)
{
    ll totalnum=0;
        vector<pll> nextpt;
        for (ll i=1; i<=r; i++)
        {
            ll j=(int) sqrt(r*r-i*i);
            if (j<0)
            j=0;
            while (i*i+j*j>r*r)
            j--;
            while (i*i+(j+1)*(j+1)<=r*r)
                j++;
            totalnum+=j;
            j++;
            while (i*i+j*j<(r+1)*(r+1))
            {
            if (i<j)
                nextpt.push_back(pll (i*i+j*j, 8));
            else if (i==j)
                nextpt.push_back(pll (2*j*j, 4));
            //cout << r << " " << i << " " << j << endl;
            j++;
            }
        }
        totalnum*=4;
        //cout << r << " " << totalnum << endl;
        if (totalnum>=n)
        {
            cout << r << endl;
            return true;
        }
        else
        {
            sort(nextpt.begin(), nextpt.end());
            for (int i=0; i<nextpt.size(); i++)
            {
                totalnum+=nextpt[i].second;
                //cout << r << " " << i << " " << nextpt[i].first << " " << nextpt[i].second << endl;
                if (totalnum>=n)
                {
                    cout << fixed << setprecision(10) << sqrt(nextpt[i].first) << endl;
                    return true;
                }
            }
        }
        //cout << r << " " << totalnum << endl;
        return false;
}

int main()
{
    cin >> n;
    ll r=(int) sqrt(n/M_PI);
    r--;
    if (r<0)
        r=0;
    n++;

        bool flag=false;
        while (!flag)
        {
            flag=findmin(r);
            r++;
        }
}