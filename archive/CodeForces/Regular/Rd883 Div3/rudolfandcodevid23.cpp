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

ll str_to_bin(str s) {
    ll rv = 0;
    FOR (i, sz(s)) {
        rv *= 2;
        rv += s[i] - '0';
    }
    return rv;
}

ll dijkstra(ll s, ll t, vector<vector<pair<ll, ll>>> &adj) {
    vector<ll> dist(sz(adj), -1);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dist[u] != -1) {
            continue;
        }
        dist[u] = d;
        if (u == t) {
            return d;
        }
        FORE (v, adj[u]) {
            if (dist[v.first] == -1) {
                pq.push({d + v.second, v.first});
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n, m, s0;
        cin >> n >> m;
        ll mask = (1 << n) - 1;
        str str0;
        cin >> str0;
        s0 = str_to_bin(str0);
        // days, from, to
        vector<tuple<ll, str, str>> raw_meds(m);
        vector<tuple<ll, ll, ll>> meds(m);
        FOR (i, m) {
            ll d;
            str s, t;
            cin >> d >> s >> t;
            raw_meds[i] = {d, s, t};
            meds[i] = {d, mask ^ str_to_bin(s), str_to_bin(t)};
        }
        vector<vector<pair<ll, ll>>> adj(1 << n);
        FOR (i, 1 << n) {
            FORE (med, meds) {
                auto [d, s, t] = med;
                adj[i].pb({(i & s) | t, d});
            }
        }
        ll rv = dijkstra(s0, 0, adj);
        cout << rv << '\n';
    }

    return 0;
}