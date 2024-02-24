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
 
const ll INF = 1e18;
 
struct Edge { ll s, t, cap = 0, cost = 0, flow = 0; };
 
struct Dinic {
    ll n; vector<Edge> edges;
    vector<vector<ll>> adj;
    vector<ll> lvl, ptr;
    queue<ll> q;
 
    Dinic(ll n, vector<Edge> &edges0) :
        n(n), adj(n), lvl(n), ptr(n) {
        for (Edge &e : edges0) {
            adj[e.s].pb(sz(edges));
            edges.pb(e);
            adj[e.t].pb(sz(edges));
            edges.pb({e.t, e.s});
        }
    }
 
    bool bfs(ll s, ll t) {
        lvl.assign(n, -1); lvl[s] = 0; q.push(s);
        while (!q.empty()) {
            ll v = q.front(); q.pop();
            for (ll &e : adj[v]) {
                ll u = edges[e].t;
                if (lvl[u] != -1 || edges[e].cap <= edges[e].flow) continue;
                lvl[u] = lvl[v] + 1;
                q.push(u);
            }
        }
        return lvl[t] != -1;
    }
 
    ll dfs(ll v, ll t, ll f) {
        if (v == t || f == 0) return f;
        for (ll &cid = ptr[v]; cid < sz(adj[v]); cid++) {
            ll e = adj[v][cid], u = edges[e].t;
            if (lvl[v] + 1 != lvl[u]) continue;
            ll pushed = dfs(u, t, min(f, edges[e].cap - edges[e].flow));
            if (pushed) {
                edges[e].flow += pushed;
                edges[e ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
 
    ll max_flow(ll s, ll t) {
        ll flow = 0;
        while (bfs(s, t)) {
            ptr.assign(n, 0);
            while (ll pushed = dfs(s, t, INF)) flow += pushed;
        }
        return flow;
    }
};
bool grid[26][500];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
 
    ll g, l; cin >> g >> l;
 
    vector<ch> word(l, 0);
    vector<bool> black(26, false);
    vector<int> num(26, 0);
    memset(grid, true, sizeof(grid));
 
    FOR(i, g - 1) {
        str guess, colors;
        cin >> guess >> colors;
        vector<int> cnt(26, 0);
        for (int j=0; j<l; j++)
        {
            if (colors[j]=='G')
            {
                word[j]=guess[j];
                cnt[word[j]-'a']++;
            }
            else if (colors[j]=='B')
            {
                black[guess[j]-'a']=true;
                grid[guess[j]-'a'][j]=false;
            }
            else
            {
                cnt[guess[j]-'a']++;
                grid[guess[j]-'a'][j]=false;
            }
        }
        for (int j=0; j<26; j++)
            num[j]=max(num[j], cnt[j]);
    }
    
    vector<Edge> ouredge;
    for(int i = 0; i < l; i++) {
        ouredge.pb(Edge {0, i + 1, 1});
    }
    for (int i = 0; i < l; i++) {
        if (word[i] != 0) {
            ouredge.pb(Edge {i + 1, word[i] - 'a' + l + 1, 1});
        }
        else {
            for (int j = 0; j < 26; j++) {
                if (grid[j][i]) ouredge.pb(Edge {i + 1, j + l + 1, 1});
            }
        }
    }
    ll lower_sum = 0;
    for (int i=0; i<26; i++)
    {
        ouredge.pb(Edge {i + l + 1, l + 28, num[i]});
        lower_sum += num[i];
        if (!black[i]) {
            ouredge.pb(Edge {i + l + 1, l + 27, l - num[i]});
        }
    }

    ouredge.pb(Edge {l + 27, l + 28, l - lower_sum});
    Dinic d=Dinic(29+l, ouredge);
    d.max_flow(0, 28+l);
    for (auto e : d.edges)
    {
        if (e.s > 0 && e.s <= l && e.t > l && e.t < l+27 && e.flow==e.cap)
        {
            // cout << e.s << " " << e.t << endl;
            word[e.s - 1] = 'a'+e.t-l-1;
        }
    }

    for (auto c : word) cout << c;
    cout << endl;
 
    return 0;
}