#include <iostream>
#include <algorithm>
using namespace std;

int levels[1000001];
int n;
int main()
{
    int minlevel=100;
    cin >> n;
    for (int i=0; i<n; i++)
    {
        cin >> levels[i];
        minlevel=min(minlevel, levels[i]);
    }
    int mincnt=0;
    int mincnt1=0;
    for (int i=0; i<n; i++)
    {
        if (levels[i]==minlevel)
        {
            mincnt++;
        }
        else if (levels[i]==minlevel+1)
        {
            mincnt1++;
        }
    }
    
    if (minlevel>=99)
    {
        cout << "possible" << endl;
        return 0;
    }
    
    for (int i=0; i<n; i++)
    {
        if (levels[i]==100)
        {
            cout << "impossible" << endl;
            return 0;
        }
    }
    if (mincnt*minlevel+mincnt1*(minlevel+1)>=n)
    {
        cout << "possible" << endl;
    }
    else
    {
        cout << "impossible" << endl;
    }
}