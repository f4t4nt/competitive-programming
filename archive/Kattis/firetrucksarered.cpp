#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FORE(x, C) for(auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

bool vis[200005];
vector<pair<int, int>> adj[200005];
vector<pair<pair<int, int>, int>> connect;
 
void dfs(int n) {
    vis[n] = true;
    for (pair<int, int> a : adj[n]) {
        if (!vis[a.first]) {
            connect.push_back({{n, a.first}, a.second});
            dfs(a.first);
        }
    }
}
 
int32_t main() {
    int n;
    cin >> n;
    
    vector<int> data[n];
    
    for (int i = 0 ; i < n ; i++) {
        int m;
        cin >> m;
        
        for (int j = 0 ; j < m ; j++) {
            int x;
            cin >> x;
            
            data[i].push_back(x);
        }
    }
    
    map<int, int> last_seen;
    
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < data[i].size() ; j++) {
            last_seen[data[i][j]] = -1;
        }
    }
    
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < data[i].size() ; j++) {
            if (last_seen[data[i][j]] != -1) {
                adj[last_seen[data[i][j]]].push_back({i, data[i][j]});
                adj[i].push_back({last_seen[data[i][j]], data[i][j]});
            }
            
            last_seen[data[i][j]] = i;
        }
    }
    
    dfs(0);
    
    if (connect.size() != n-1) {
        cout << "impossible" << '\n';
    }
    else {
        for (int i = 0 ; i < connect.size() ; i++) {
            cout << connect[i].first.first+1 << " " << connect[i].first.second+1 << " " << connect[i].second << '\n';
        }
    }
}