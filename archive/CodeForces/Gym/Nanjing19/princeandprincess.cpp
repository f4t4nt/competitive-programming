#include <iostream>
using namespace std;

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    if (b+c>=a)
    {
        cout << "NO" << endl;
        return 0;
    }
    if (a==1 && b==0 && c==0)
    {
        cout << "YES" << endl;
        cout << "0" << endl;
        return 0;
    }
    cout << "YES" << endl;
    cout << 2*(b+c)+1 << endl;
}