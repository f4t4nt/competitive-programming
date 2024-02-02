#include <iostream>
#include <stack>
#include <vector>
#include <queue>
using namespace std;

vector<int> adj[100002];
int outdegree[100002];
int adjA[100002];
int adjB[100002];
bool vis1[100002];
bool vis2[100002];
int arr1[100002];
int arr2[100002];
int main()
{
    int n;
    int x;
    cin >> n;
    stack<int> s1;
    int totaledge=0;
    for (int i=0; i<n; i++)
    {
        cin >> x;
        arr1[i]=x;
        while (!s1.empty() && s1.top()<x)
        {
            s1.pop();
        }
        if (!s1.empty())
        {
            adj[s1.top()].push_back(x);
            outdegree[x]++;
            totaledge++;
            //adjA[s1.top()].push_back(x);
        }
        s1.push(x);
    }
    stack<int> s2;
    for (int i=0; i<n; i++)
    {
        cin >> x;
        arr2[i]=x;
        while (!s2.empty() && s2.top()>x)
        {
            s2.pop();
        }
        if (!s2.empty())
        {
            adj[s2.top()].push_back(x);
            outdegree[x]++;
            totaledge++;
            //adjB[s1.top()].push_back(x);
        }
        s2.push(x);
    }
    
    for (int i=0; i<n; i++)
    {
        vis1[arr1[i]]=true;
        for (int j=0; j<adj[arr1[i]].size(); j++)
        {
            if (vis1[adj[arr1[i]][j]])
            {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    
    for (int i=0; i<n; i++)
    {
        vis2[arr2[i]]=true;
        for (int j=0; j<adj[arr2[i]].size(); j++)
        {
            if (vis2[adj[arr2[i]][j]])
            {
                cout << "No" << endl;
                return 0;
            }
        }
    }
    
    queue<int> bfs;
    for (int i=1; i<=n; i++)
    {
        if (outdegree[i]==0)
            bfs.push(i);
    }
    int cnt=0;
    while (!bfs.empty())
    {
        int x=bfs.front();
        bfs.pop();
        cnt++;
        for (int j=0; j<adj[x].size(); j++)
        {
            outdegree[adj[x][j]]--;
            if (outdegree[adj[x][j]]==0)
                bfs.push(adj[x][j]);
        }
    }
    if (cnt==n)
    {
        cout << "Yes" << endl;
        cout << totaledge << endl;
        for (int i=1; i<=n; i++)
        {
            for (int j=0; j<adj[i].size(); j++)
            {
                cout << i << " " << adj[i][j] << endl;
            }
        }
    }
    else
        cout << "No" << endl;
    
    
}