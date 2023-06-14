#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define flip(C) reverse(C.begin(), C.end())
#define ssort(C) sort(C.begin(), C.end())
#define rsort(C) sort(C.begin(), C.end(), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FOI(x, e, i) for(ll x = 0; x < (ll) e; x += (ll) i)
#define FOBI(x, b, e, i) for(ll x = (ll) b; x < (ll) e; x += (ll) i)
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, k;
    cin >> n >> m >> k;
    vector<tuple<ll, ll, ll>> edges(m);
    vector<vector<pair<ll, ll>>> adj(n);
    FOR (i, m) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        edges[i] = {u, v, w};
        adj[u].pb({v, w});
    }
    vector<ll> log(k);
    FOR (i, k) {
        cin >> log[i];
    }
    ssort(log);

    vector<ll> dist(n, LLONG_MAX), prev(n, -1);
    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<>> pq;
    if (log[0] == 0) {
        pq.push({0, 0, 1});
    } else {
        pq.push({0, 0, 0});
    }
    dist[0] = 0;
    while (!pq.empty()) {
        ll d, u, idx;
        tie(d, u, idx) = pq.top();
        pq.pop();
        if (d > dist[u]) {
            continue;
        }
        FORE (e, adj[u]) {
            ll v, w;
            tie(v, w) = e;
            if (d + w < dist[v]) {
                ll new_idx = idx;
                if (idx < k) {
                    if (d + w == log[idx]) {
                        new_idx++;
                    } elif (d + w > log[idx]) {
                        continue;
                    }
                }
                dist[v] = d + w;
                prev[v] = u;
                if (v != n - 1) {
                    pq.push({dist[v], v, new_idx});
                }
            }
        }
    }

    vector<ll> min_dist(n, LLONG_MAX);
    min_dist[0] = 0;
    pq.push({0, 0, 0});
    while (!pq.empty()) {
        ll d, u, idx;
        tie(d, u, idx) = pq.top();
        pq.pop();
        if (d > min_dist[u]) {
            continue;
        }
        FORE (e, adj[u]) {
            ll v, w;
            tie(v, w) = e;
            if (d + w < min_dist[v]) {
                min_dist[v] = d + w;
                pq.push({min_dist[v], v, 0});
            }
        }
    }

    if (dist[n - 1] == LLONG_MAX || dist[n - 1] < log[k - 1] || dist[n - 1] > min_dist[n - 1]) {
        cout << 0 << '\n';
        return 0;
    }

    vector<pair<ll, ll>> top_sort(n);
    FOR (i, n) {
        top_sort[i] = {dist[i], i};
    }
    ssort(top_sort);
    vector<ll> num(n);
    num[0] = 1;
    FOR (i, n) {
        ll u, d;
        tie(d, u) = top_sort[i];
        if (d == LLONG_MAX) {
            break;
        }
        FORE (e, adj[u]) {
            ll v, w;
            tie(v, w) = e;
            if (d + w == dist[v]) {
                num[v] = min(num[v] + num[u], 2LL);
            }
        }
    }

    if (num[n - 1] > 1) {
        cout << 1 << '\n';
        return 0;
    }

    vector<ll> path;
    ll u = n - 1;
    while (u != -1) {
        path.pb(u);
        u = prev[u];
    }
    flip(path);

    cout << sz(path) << '\n';
    FORE (u, path) {
        cout << u + 1 << '\n';
    }

    return 0;
}