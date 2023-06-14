#include <bits/stdc++.h>

using namespace std;

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

ll max_flow(ll s, ll t, vector<vector<pair<ll, ll>>> adj) {
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
                if (parent[next.first] == -1 && next.second > 0) {
                    parent[next.first] = cur;
                    q.push(next.first);
                }
            }
        }
        if (parent[t] == -1) break;
        ll path_flow = LLONG_MAX;
        for (ll cur = t; cur != s; cur = parent[cur]) {
            ll prev = parent[cur];
            FORE (next, adj[prev]) {
                if (next.first == cur) {
                    path_flow = min(path_flow, next.second);
                    break;
                }
            }
        }
        for (ll cur = t; cur != s; cur = parent[cur]) {
            ll prev = parent[cur];
            FORE (next, adj[prev]) {
                if (next.first == cur) {
                    next.second -= path_flow;
                    break;
                }
            }
            FORE (next, adj[cur]) {
                if (next.first == prev) {
                    next.second += path_flow;
                    break;
                }
            }
        }
        flow += path_flow;
    }
    return flow;
}

int main() {
    ll s, r, f, t;
    cin >> s >> r >> f >> t;
    map<str, ll> state_map;
    vector<ll> state_type;
    FOR (i, r) {
        str material;
        cin >> material;
        state_map[material] = sz(state_map);
        state_type.pb(1);
    }
    FOR (i, f) {
        str factory;
        cin >> factory;
        state_map[factory] = sz(state_map);
        state_type.pb(2);
    }
    vector<vector<ll>> companies(t);
    FOR (i, t) {
        ll n;
        cin >> n;
        FOR (j, n) {
            str state;
            cin >> state;
            if (state_map.find(state) == state_map.end()) {
                state_map[state] = sz(state_map);
                state_type.pb(0);
            }
            companies[i].pb(state_map[state]);
        }
    }
    vector<vector<pair<ll, ll>>> adj(2 + 2 * (s + t));
    FOR (i, s + t) {
        adj[2 * i].pb(mp(2 * i + 1, 1));
        adj[2 * i + 1].pb(mp(2 * i, 0));
    }
    FORE (state, state_map) {
        if (state_type[state.second] == 1) {
            adj[2 * s + 2 * t].pb(mp(2 * state.second, 1));
            adj[2 * state.second].pb(mp(2 * s + 2 * t + 1, 0));
        } elif (state_type[state.second] == 2) {
            adj[2 * state.second + 1].pb(mp(2 * s + 2 * t + 1, 1));
            adj[2 * s + 2 * t].pb(mp(2 * state.second, 0));
        }
    }
    FOR (i, t) {
        FORE (state, companies[i]) {
            adj[2 * s + 2 * i].pb(mp(2 * state + 1, 0));
            adj[2 * state].pb(mp(2 * s + 2 * i + 1, 0));
            adj[2 * s + 2 * i + 1].pb(mp(2 * state, 1));
            adj[2 * state + 1].pb(mp(2 * s + 2 * i, 1));
        }
    }
    cout << max_flow(2 * s + 2 * t, 2 * s + 2 * t + 1, adj) << '\n';
    // FOR (i, sz(adj)) {
    //     cout << i << '\n';
    // }
    // FOR (i, sz(adj)) {
    //     FORE (edge, adj[i]) {
    //         if (edge.second == 0) continue;
    //         cout << i << ' ' << edge.first << ' ' << edge.second << '\n';
    //     }
    // }
    return 0;
}