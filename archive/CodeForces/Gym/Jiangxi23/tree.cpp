#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <fstream>
#include <iomanip>
#include <random>
#include <stack>
#include <set>
 
using namespace std;
 
#define pb push_back
#define mp make_pair
#define rep(i, n) for (int i = 0 ; i < n ; i++)
#define rrep(i, a, n) for (int i = a ; i < n ; i++)
#define per(i, n) for (int i = n - 1 ; i >= 0 ; i--)
#define all(x) begin(x), end(x)
#define int long long
#define sz(x) (int) (x).size()
 
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef tuple<int, int, int> iii;
typedef vector<iii> viii;
typedef priority_queue<int> pqi;
typedef priority_queue<ii> pqii;
typedef map<int, int> mii;
typedef map<int, string> mis;
typedef map<string, int> msi;
typedef map<ll, ll> mll;
typedef queue<int> qi;
typedef queue<ii> qii;
typedef pair<ll, ll> iil;
typedef vector<iil> viil;
typedef vector<vi> vvi;
 
ll MOD = 1000000007;
ll INF = 1LL * 2000000000 * 2000000000;
 
double PI = 3.1415926535897932;

void solve() {
    
    int n, q;
    cin >> n >> q;
    
    vii adj[n];
    
    rep(i, n - 1) {
        int x, y, w;
        cin >> x >> y >> w;
        
        x--; y--;
        
        adj[x].pb({y, w});
        adj[y].pb({x, w});
    }
    
    int val[n];
    rep(i, n) val[i] = 0;
    rep(i, n) {
        rep(j, adj[i].size()) {
            val[i] ^= (adj[i][j].second);
        }
    }
    
    rep(i, q) {
        int c;
        cin >> c;
        
        if (c == 1) {
            int x, y, z;
            cin >> x >> y >> z;
            
            x--; y--;
            
            val[x] ^= z;
            val[y] ^= z;
        }
        else {
            int x;
            cin >> x;
            
            x--;
            
            cout << val[x] << '\n';
        }
    }
    
}
 
void querySolve() {
    
    int t;
    cin >> t;
 
    rep(i, t) {
        solve();
    }
}
 
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    //querySolve();
}