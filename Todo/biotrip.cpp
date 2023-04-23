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

// https://open.kattis.com/problems/biotrip

map<pair<ll, ll>, ll> road_to_idx;
vector<ll> as;

struct Junction {
    ll idx, m;
    vector<tuple<ll, ll, ll>> path;

    Junction(ll i) {
        this->idx = i;
        cin >> m;
        path.resize(m);
        FOR (j, m) {
            ll d, t, a;
            cin >> d >> t >> a;
            d--;
            path[j] = {d, t, a};
            assert(road_to_idx.find({idx, d}) == road_to_idx.end());
            road_to_idx[{idx, d}] = sz(road_to_idx);
            as.pb(a);
        }
    }
};

void gen_adj(ll &a1, ll &a2,
    vector<vector<pair<ll, ll>>> &adj,
    vector<Junction> &junctions)
{
    FORE (j, junctions) {
        FORE (p, j.path) {
            ll d, t, a;
            tie(d, t, a) = p;
            adj[road_to_idx[{j.idx, d}]].pb({road_to_idx[{d, j.idx}], t});
            a = (a + 180) % 360;
            ll a_lo = (a - a2 + 360) % 360, a_hi = (a + a1) % 360;
            while (a_lo > a_hi) {
                a_hi += 360;
            }
            FORE (q, j.path) {
                ll dq, tq, aq;
                tie(dq, tq, aq) = q;
                if ((a_lo <= aq && aq <= a_hi) ||
                    (a_lo <= aq + 360 && aq + 360 <= a_hi)) {
                    adj[road_to_idx[{j.idx, d}]].pb({road_to_idx[{dq, j.idx}], tq});
                }
            }
        }
    }
}

void bfs(vector<vector<pair<ll, ll>>> &adj, vector<ll> &dist, bool tagback) {
    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<>> pq;
    FOR (i, sz(adj)) {
        if (dist[i] != 1e15) {
            pq.push({dist[i], i, -1});
        }
    }
    while (!pq.empty()) {
        ll u, d, p;
        tie(d, u, p) = pq.top();
        pq.pop();
        if (dist[u] < d) {
            continue;
        }
        FORE (v, adj[u]) {
            if (!tagback && v.first == p) {
                continue;
            }
            if (dist[v.first] > dist[u] + v.second) {
                dist[v.first] = dist[u] + v.second;
                pq.push({dist[v.first], v.first, u});
            }
        }
    }
}

bool connectable(ll a_in, ll a_out, ll a1, ll a2) {
    a_in = (a_in + 180) % 360;
    ll a_lo = (a_in - a2 + 360) % 360, a_hi = (a_in + a1) % 360;
    while (a_lo > a_hi) {
        a_hi += 360;
    }
    return (a_lo <= a_out && a_out <= a_hi) ||
        (a_lo <= a_out + 360 && a_out + 360 <= a_hi);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    road_to_idx.clear();
    as.clear();

    ll n, t, a1, a2;
    cin >> n >> t >> a1 >> a2;
    t--;
    vector<Junction> junctions;
    FOR (i, n) {
        junctions.pb(Junction(i));
    }
    vector<vector<pair<ll, ll>>> adj(sz(road_to_idx));
    gen_adj(a1, a2, adj, junctions);
    vector<ll> dist(sz(road_to_idx), 1e15);
    FORE (x, junctions[0].path) {
        ll d, t, a;
        tie(d, t, a) = x;
        dist[road_to_idx[{0, d}]] = 0;
    }
    bfs(adj, dist, (a1 == 180 || a2 == 180));
    set<ll> asdf;
    set<pair<ll, ll>> tmp;
    FORE (x, road_to_idx) {
        ll u, v;
        tie(u, v) = x.first;
        if (u == t) {
            asdf.insert(x.second);
            tmp.insert({dist[x.second], x.second});
        }
        dist[x.second] = 1e15;
    }
    FORE (x, tmp) {
        FORE (y, tmp) {
            ll a_in = as[x.second], a_out = as[y.second];
            if (connectable(a_in, a_out, a1, a2)) {
                dist[y.second] = min(dist[y.second], x.first);
            }
        }
    }
    FORE (x, tmp) {
        ll u = x.second;
        while (sz(adj[u]) > 1) {
            adj[u].pop_back();
        }
    }
    FORE (x, adj) {
        FORE (y, x) {
            if (asdf.find(y.first) != asdf.end()) {
                y.second = 1e6;
            }
        }
    }
    bfs(adj, dist, (a1 == 180 || a2 == 180));
    ll rv = 1e15;
    FORE (x, road_to_idx) {
        ll u, v;
        tie(u, v) = x.first;
        if (u == 0) {
            rv = min(rv, dist[x.second]);
        }
    }
    if (rv >= 1e15) {
        cout << "impossible\n";
    } else {
        cout << rv << '\n';
    }

    return 0;
}