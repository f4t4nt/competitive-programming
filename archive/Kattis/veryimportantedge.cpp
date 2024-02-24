#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<int, int> pii;

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)
#define pb push_back

int n, m;

int root[100001];
int height[100001];
bool intree[1000000];
vector<int> adj[100001];
int parent[100001];
int topchain[100001];
int lcatable[100001][20];
int weight[100001];
bool didedge[100001];
int depth[100001];

struct edge
{
    int s;
    int e;
    int l;
};
edge Edges[1000000];
bool compare(edge a, edge b)
{
    return a.l<b.l;
}
int FindRoot(int x)
{
    if (x!=root[x]) root[x]=FindRoot(root[x]);
    return root[x];
}

bool Merge(int x, int y)
{
    x=FindRoot(x);
    y=FindRoot(y);
    if (x==y) return false;
    if (height[x]<height[y]) root[x]=y;
    else
    {
        root[y]=x;
        if (height[x]==height[y]) height[x]++;
    }
    return true;
}

bool visited[100001];

void buildtree(int x)
{
    visited[x]=true;
    //cout << x << " " << parent[x] << endl;
    for (int i=0; i<adj[x].size(); i++)
    {
        if (visited[adj[x][i]])
            continue;
        depth[adj[x][i]]=depth[x]+1;
        parent[adj[x][i]]=x;
        topchain[adj[x][i]]=x;
        lcatable[adj[x][i]][0]=x;
        buildtree(adj[x][i]);
    }
}

int lca(int u, int v)
{
    int k=19;
    while (k>=0)
    {
        int d=1<<k;
        if (depth[u]>=depth[v]+d)
            u=lcatable[u][k];
        else if (depth[v]>=depth[u]+d)
            v=lcatable[v][k];
        k--;
    }
    k=19;
    while (k>=0)
    {
        if (lcatable[u][k]!=lcatable[v][k])
        {
            u=lcatable[u][k];
            v=lcatable[v][k];
        }
        k--;
    }
    if (u!=v)
    {
        u=parent[u];
        v=parent[v];
    }
    return u;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int s, e, l;
    cin >> n >> m;
    for (int i=0; i<m; i++)
    {
        cin >> Edges[i].s >> Edges[i].e >> Edges[i].l;
    }
    sort(Edges, Edges+m, compare);
    for (int i=1; i<=n; i++)
        root[i]=i;
    
    for (int i=0; i<m; i++)
    {
        if (Merge(Edges[i].s, Edges[i].e))
        {
            intree[i]=true;
            adj[Edges[i].s].pb(Edges[i].e);
            adj[Edges[i].e].pb(Edges[i].s);
        }
    }
    buildtree(1);
    for (int i=0; i<m; i++)
    {
        if (intree[i])
        {
            int x=Edges[i].s;
            int y=Edges[i].e;
            if (parent[x]==y)
                weight[x]=Edges[i].l;
            else
                weight[y]=Edges[i].l;
        }
    }
    lcatable[1][0]=1;
    int ans=0;
    for (int k=1; k<20; k++)
    {
        for (int i=1; i<=n; i++)
        {
            lcatable[i][k]=lcatable[lcatable[i][k-1]][k-1];
        }
    }
    for (int i=0; i<m; i++)
    {
        if (intree[i])
            continue;
        int x=Edges[i].s;
        int y=Edges[i].e;
        int w=Edges[i].l;
        int minedge=1000000;
        int z=lca(x, y);
        int newtop=topchain[z];
        if (!didedge[z])
            newtop=z;
        while (depth[x]>depth[z])
        {
            if (!didedge[x])
                minedge=min(minedge, weight[x]);
            didedge[x]=true;
            int temp=topchain[x];
            topchain[x]=newtop;
            x=temp;
        }
        while (depth[y]>depth[z])
        {
            if (!didedge[y])
                minedge=min(minedge, weight[y]);
            didedge[y]=true;
            int temp=topchain[y];
            topchain[y]=newtop;
            y=temp;
        }
        ans=max(ans, w-minedge);
    }
    ll endans=0;
    for (int i=0; i<m; i++)
    {
        if (intree[i])
            endans+=(ll) Edges[i].l;
    }
    cout << endans+(ll) ans << endl;


}