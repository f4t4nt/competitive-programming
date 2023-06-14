#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int largestsize=0;
int m;
vector<int> elts;
int cur;


int main()
{
    cin >> m;
    for (int i=0; i<m; i++)
    {
        cin >> cur;
        elts.push_back(cur);
        largestsize=max(largestsize, cur);
    }
    string flag="no";
    for (int i=0; i<m; i++)
    {
        if (elts[i]==largestsize/2)
        {
            flag="yes";
            break;
        }
    }
    cout << flag << endl;
}