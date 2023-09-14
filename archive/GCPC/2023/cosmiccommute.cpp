#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <set>
#include <queue>

using namespace std;

#define int long long

typedef vector<int> vi;
typedef pair<int, int> ii;

#define rep(i, n) for (int i = 0 ; i < n ; i++)
#define rrep(i, a, b) for (int i = a ; i < b ; i++)
#define pb push_back

int INF = 2000000000LL;

int gcd(int a, int b) {
    if (b > a) swap(a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}

int32_t main() {
    
    int n, m, k;
    cin >> n >> m >> k;
    
    vi a(k);
    rep(i, k) cin >> a[i];
    rep(i, k) a[i]--;
    
    vi adj[n];
    
    rep(i, m) {
        int a, b;
        cin >> a >> b;
        
        a--; b--;
        
        adj[a].pb(b);
        adj[b].pb(a);
    }
    
    queue<ii> q;
    
    int fd[n];
    int rd[n];
    
    rep(i, n) {
        fd[i] = INF;
        rd[i] = INF;
    }
    
    q.push({0, 0});
    
    while (q.size()) {
        ii inf = q.front();
        
        q.pop();
        
        int vt = inf.first;
        int ds = inf.second;
        
        if (ds >= fd[vt]) continue;
        
        fd[vt] = ds;
        
        for (int a : adj[vt]) {
            if (ds + 1 < fd[a]) {
                q.push({a, ds + 1});
            }
        }
    }
    
    q.push({n - 1, 0});
    
    while (q.size()) {
        ii inf = q.front();
        
        q.pop();
        
        int vt = inf.first;
        int ds = inf.second;
        
        if (ds >= rd[vt]) continue;
        
        rd[vt] = ds;
        
        for (int a : adj[vt]) {
            if (ds + 1 < rd[a]) {
                q.push({a, ds + 1});
            }
        }
    }
    
    //a / b >= c / d
    //a1 * b2 >= b1 * a2
    
    int ma = fd[n - 1];
    int mb = 1;
    
    int td = 0;
    
    rep(i, k) {
        td += rd[a[i]];
    }
    
   // cout << td << endl;
    
    rep(i, k) {
        int ca = td - rd[a[i]] + (k - 1) * fd[a[i]];
        int cb = k - 1;
        
      //  cout << a[i] << " " << td << " " << rd[a[i]] << " " ca << " " << cb << endl;
        
        if (ca * mb <= cb * ma) {
            ma = ca;
            mb = cb;
        }
    }
    
    int g = gcd(ma, mb);
    
    ma /= g;
    mb /= g;
    
    cout << ma << "/" << mb << '\n';
}