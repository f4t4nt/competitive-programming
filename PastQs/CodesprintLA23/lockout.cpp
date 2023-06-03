#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

int n;
ll coins[100001];
ll times[100001];
ll luigi[100001];
//ll revluigi[100001];
ll sum=0;
//ll revmario[100001];
ll mario[100001];

int main()
{
    cin >> n;
    for (int i=1; i<=n; i++)
    {
        cin >> coins[i];
        sum+=coins[i];
    }
    for (int i=1; i<=n; i++)
    {
        cin >> times[i];
    }
    for (int i=1; i<=n; i++)
    {
        cin >> luigi[i];
        //revluigi[luigi[i]]=i;
    }
    if (sum>2*coins[luigi[1]])
    {
        cout << 1 << endl;
        for (int i=1; i<n; i++)
        {
            cout << luigi[i+1] << " ";
        }
        cout << luigi[1] << endl;
        return 0;
    }
    else if (sum<2*coins[luigi[1]])
    {
        cout << 0.5 << endl;
        for (int i=1; i<n; i++)
        {
            cout << luigi[i] << " ";
        }
        cout << luigi[n] << endl;
        return 0;
    }
    else if (sum==2*coins[luigi[1]])
    {
        if (n>2)
        {
            cout << 0.5 << endl;
            cout << luigi[1] << " ";
            for (int i=3; i<=n; i++)
            {
                cout << luigi[i] << " ";
            }
            cout << luigi[2] << endl;
            return 0;
        }
        else
        {
            cout << 0.25 << endl;
            cout << luigi[1] << " " << luigi[2] << endl;
        }
    }
}