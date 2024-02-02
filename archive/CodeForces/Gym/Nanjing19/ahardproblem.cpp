#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    for (int i=0; i<n; i++)
    {
        long long t;
        cin >> t;
        if ((t%2==0))
            cout << t/2+1 << endl;
        else
            cout << (t+1)/2+1 << endl;
    }
}