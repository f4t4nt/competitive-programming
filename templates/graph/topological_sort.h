#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define pb push_back
#define sz(C) (ll) C.size()

vector<ll> top_sort(vector<vector<ll>> &adj, vector<ll> deg = {}) { // deg is in-degree
    if (deg.empty()) {
        deg.resize(sz(adj));
        for (ll i = 0; i < sz(adj); i++)
            for (ll v : adj[i])
                deg[v]++;
    }
    ll n = sz(adj);
    vector<ll> ord; queue<ll> q;
    for (ll i = 0; i < n; i++)
        if (deg[i] == 0) q.push(i);
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        ord.pb(u);
        for (ll v : adj[u])
            if (--deg[v] == 0) q.push(v);
    }
    return ord;
}
