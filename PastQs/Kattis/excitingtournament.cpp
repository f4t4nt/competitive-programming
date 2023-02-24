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
#define ins insert
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

ll max_flow(ll s, ll t, vector<vector<tuple<ll, ll, ll>>> adj) {
    ll flow = 0;
    vector<ll> parent(sz(adj));
    while (true) {
        fill(parent.begin(), parent.end(), -1);
        queue<ll> q;
        q.push(s);
        parent[s] = -2;
        while (!q.empty()) {
            ll cur = q.front();
            q.pop();
            FORE (next, adj[cur]) {
                if (parent[get<0>(next)] == -1 && get<1>(next) > 0) {
                    parent[get<0>(next)] = cur;
                    q.push(get<0>(next));
                }
            }
        }
        if (parent[t] == -1) break;
        ll path_flow = LLONG_MAX;
        for (ll cur = t; cur != s; cur = parent[cur]) {
            ll prev = parent[cur];
            FORE (next, adj[prev]) {
                if (get<0>(next) == cur) {
                    path_flow = min(path_flow, get<1>(next));
                    break;
                }
            }
        }
        for (ll cur = t; cur != s; cur = parent[cur]) {
            ll prev = parent[cur];
            FORE (next, adj[cur]) {
                if (get<0>(next) == prev) {
                    get<1>(next) += path_flow;
                    break;
                }
            }
            FORE (next, adj[prev]) {
                if (get<0>(next) == cur) {
                    get<1>(next) -= path_flow;
                    break;
                }
            }
        }
        flow += path_flow;
    }
    return flow;
}

ll min_cost_flow(ll s, ll t, ll target_flow, vector<vector<tuple<ll, ll, ll>>> adj) {
    ll flow = 0, cost = 0;
    vector<ll> dist(sz(adj)), parent(sz(adj));
    while (flow < target_flow) {
        vector<bool> in_queue(sz(adj), false);
        fill(dist.begin(), dist.end(), LLONG_MAX);
        fill(parent.begin(), parent.end(), -1);
        queue<ll> q;
        q.push(s);
        dist[s] = 0;
        in_queue[s] = true;
        while (!q.empty()) {
            ll cur = q.front();
            q.pop();
            in_queue[cur] = false;
            FORE (next, adj[cur]) {
                if (get<1>(next) > 0 && dist[get<0>(next)] > dist[cur] + get<2>(next)) {
                    dist[get<0>(next)] = dist[cur] + get<2>(next);
                    parent[get<0>(next)] = cur;
                    if (!in_queue[get<0>(next)]) {
                        q.push(get<0>(next));
                        in_queue[get<0>(next)] = true;
                    }
                }
            }
        }
        if (parent[t] == -1) break;
        ll path_flow = target_flow - flow;
        for (ll cur = t; cur != s; cur = parent[cur]) {
            ll prev = parent[cur];
            FORE (next, adj[prev]) {
                if (get<0>(next) == cur) {
                    path_flow = min(path_flow, get<1>(next));
                    break;
                }
            }
        }
        flow += path_flow;
        cost += path_flow * dist[t];
        for (ll cur = t; cur != s; cur = parent[cur]) {
            ll prev = parent[cur];
            FORE (next, adj[cur]) {
                if (get<0>(next) == prev) {
                    get<1>(next) += path_flow;
                    break;
                }
            }
            FORE (next, adj[prev]) {
                if (get<0>(next) == cur) {
                    get<1>(next) -= path_flow;
                    break;
                }
            }
        }
    }

    if (flow < target_flow) {
        return -1;
    } else  {
        return cost;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n;
    cin >> n;
    // skill, max games
    vector<pair<ll, ll>> players(n);
    FOR (i, n) {
        cin >> players[i].first >> players[i].second;
    }
    ssort(players);
    ll source = 2 * n, sink = 2 * n + 1;
    vector<vector<tuple<ll, ll, ll>>> adj(2 * n + 2);
    FOR (i, n) {
        FOB (j, i + 1, n) {
            adj[i].pb({j + n, 1, players[j].first ^ players[i].first});
            adj[j + n].pb({i, 0, -(players[j].first ^ players[i].first)});
        }
    }
    FOR (i, n) {
        adj[source].pb({i, 1, 0});
        adj[i].pb({source, 0, 0});
    }
    FOR (i, n - 1) {
        adj[i + n].pb({sink, players[i].second - 1, 0});
        adj[sink].pb({i + n, 0, 0});
    }
    adj[n - 1 + n].pb({sink, players[n - 1].second, 0});
    adj[sink].pb({n - 1 + n, 0, 0});

    ll flow = max_flow(source, sink, adj);
    ll min_cost = min_cost_flow(source, sink, flow, adj);
    FOR (i, sz(adj)) {
        FORE (next, adj[i]) {
            get<2>(next) = -get<2>(next);
        }
    }
    ll max_cost = -min_cost_flow(source, sink, flow, adj);
    cout << min_cost << ' ' << max_cost << '\n';

    return 0;
}