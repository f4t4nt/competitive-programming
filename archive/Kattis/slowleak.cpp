#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using cd = complex<double>;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define mp make_pair
#define mt make_tuple
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

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

constexpr ll INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, t, d;
    cin >> n >> m >> t >> d;
    vector<vector<pair<ll, ll>>> adj(n);
    map<ll, vector<pair<ll, ll>>> adj_s;
    adj_s[0] = {};
    adj_s[n - 1] = {};
    FOR (i, t) {
        ll r;
        cin >> r;
        r--;
        adj_s[r] = {};
    }
    FOR (i, m) {
        ll a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        adj[a].pb({b, c});
        adj[b].pb({a, c});
    }

    FORE (elem, adj_s) {
        ll r;
        tie(r, ignore) = elem;
        vector<ll> dist(n, INF);
        dist[r] = 0;
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
        pq.push({0, r});
        while (!pq.empty()) {
            ll cur_d, u;
            tie(cur_d, u) = pq.top();
            pq.pop();
            if (d < cur_d) {
                break;
            }
            if (cur_d > dist[u]) {
                continue;
            }
            FORE (elem, adj[u]) {
                ll v, w;
                tie(v, w) = elem;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        FOR (i, n) {
            if (i != r && adj_s.find(i) != adj_s.end() && dist[i] <= d) {
                adj_s[r].pb({i, dist[i]});
            }
        }
    }

    vector<ll> dist(n, INF);
    dist[0] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        ll cur_d, u;
        tie(cur_d, u) = pq.top();
        pq.pop();
        if (cur_d > dist[u]) {
            continue;
        }
        FORE (elem, adj_s[u]) {
            ll v, w;
            tie(v, w) = elem;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[n - 1] == INF) {
        cout << "stuck\n";
    } else {
        cout << dist[n - 1] << '\n';
    }

    return 0;
}