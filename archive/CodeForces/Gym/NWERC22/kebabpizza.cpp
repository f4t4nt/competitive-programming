#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define x first
#define y second
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

bool doub[100001];
// vector<int> adj[100001];
set<int> adj[100001];
int n, k;
int p[100001];
// bool vis[100001];
bitset<100001> vis;
int cycle=-1;
int cycparent=-1;
// bool incycle[100001];
bitset<100001> incycle;
void findcycle(int v)
{
    if (cycle>-1)
        return;
    vis[v]=true;
    // for (int i=0; i<adj[v].size(); i++)
    for (int i : adj[v])
    {
        // if (p[v]==adj[v][i])
        if (p[v] == i)
            continue;
        // if (vis[adj[v][i]])
        if (vis[i])
        {
            cycle=v;
            // cycparent=adj[v][i];
            cycparent=i;
            return;
        }
        // p[adj[v][i]]=v;
        // findcycle(adj[v][i]);
        p[i]=v;
        findcycle(i);
        if (cycle>-1)
            return;
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i=0; i<n; i++)
    {
        int a, b;
        cin >> a >> b;
        if (a==b)
            doub[a]=true;
        else
        {
            adj[a].insert(b);
            adj[b].insert(a);
        }
    }
    n=k;
    // for (int i=1; i<=n; i++)
    // {
    //     adj[i] = vector<int>(all(adj2[i]));
    // }
    for (int i=1; i<=n; i++)
        if (!vis[i] && cycle==-1)
            findcycle(i);
    //vector<int> cyclist;
    if (cycle!=-1)
    {
        incycle[cycle]=true;
        //cyclist.pb(cycle);
        int cur=cycle;
        while (cur!=cycparent)
        {
            cur=p[cur];
            //cyclist.pb(cur);
            incycle[cur]=true;
        }
    }
    if (cycle>-1)
    {
        for (int i=1; i<=n; i++)
        {
            // for (int j=0; j<adj[i].size(); j++)
            // {
            //     if (!incycle[i] && !incycle[adj[i][j]])
            //     {
            //         cout << "impossible" << endl;
            //         return 0;
            //     }
            // }
            for (int j : adj[i]) {
                if (!incycle[i] && !incycle[j]) {
                    cout << "impossible" << endl;
                    return 0;
                }
                if (incycle[i] && incycle[j])
                {
                    if (p[i]!=j && p[j]!=i && !((i==cycle && j==cycparent) || (j==cycle && i==cycparent)))
                    {
                        cout << "impossible" << endl;
                        return 0;
                    }
                }
            }
            if (!incycle[i] && (adj[i].size()>1 || doub[i]))
            {
                cout << "impossible" << endl;
                return 0;
            }
        }
        cout << "possible" << endl;
        return 0;
    }
    for (int i=1; i<=n; i++)
    {
        int cnt=adj[i].size();
        // for (int j=0; j<adj[i].size(); j++)
        // {
        //     if (adj[adj[i][j]].size()==1 && !doub[adj[i][j]])
        //         cnt--;
        // }
        for (int j : adj[i]) {
            if (adj[j].size() == 1 && !doub[j]) cnt--;
        }
        if (cnt>2)
        {
            cout << "impossible" << endl;
            return 0;
        }
    }
    cout << "possible" << endl;

}