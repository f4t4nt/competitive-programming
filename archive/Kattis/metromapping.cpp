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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll m, n, a;
    cin >> m >> n >> a;
    // [line][station_from] -> station_to
    vector<vector<vector<ll>>> adj(n, vector<vector<ll>>(m));
    vector<vector<ll>> lines(n), stations(m);
    FOR (i, n) {
        ll sz;
        cin >> sz;
        lines[i].resize(sz);
        FOR (j, sz) {
            cin >> lines[i][j];
            lines[i][j]--;
            stations[lines[i][j]].pb(i);
        }
        FOR (j, sz) {
            if (j > 0) {
                adj[i][lines[i][j - 1]].pb(lines[i][j]);
            }
            if (j < sz - 1) {
                adj[i][lines[i][j + 1]].pb(lines[i][j]);
            }
        }
    }

    ll t;
    cin >> t;
    vector<pair<ll, ll>> queries(t);
    FOR (i, t) {
        ll b;
        cin >> b;
        queries[i] = {b, i};
    }
    rsort(queries);

    // [line][station][switches] -> distance
    ll MAX_CNT = 200;
    vector<vector<vector<ll>>> dist(n, vector<vector<ll>>(m, vector<ll>(MAX_CNT, 1e18)));
    // {distance, line, station, switches}
    priority_queue<tuple<ll, ll, ll, ll>, vector<tuple<ll, ll, ll, ll>>, greater<>> pq;
    FORE (l, stations[0]) {
        dist[l][0][0] = 0;
        pq.push({0, l, 0, 0});
    }
    while (!pq.empty()) {
        ll d, l, s, cnt;
        tie(d, l, s, cnt) = pq.top();
        pq.pop();
        if (cnt == MAX_CNT) {
            continue;
        }
        if (d > dist[l][s][cnt]) {
            continue;
        }
        FORE (ns, adj[l][s]) {
            ll nd = d + a;
            if (dist[l][ns][cnt] > nd) {
                dist[l][ns][cnt] = nd;
                pq.push({nd, l, ns, cnt});
            }
        }
        if (cnt + 1 == MAX_CNT) {
            continue;
        }
        FORE (nl, stations[s]) {
            if (nl == l) {
                continue;
            }
            if (dist[nl][s][cnt + 1] > d) {
                dist[nl][s][cnt + 1] = d;
                pq.push({d, nl, s, cnt + 1});
            }
        }
    }

    vector<ll> rv(t, 1e18);
    FORE (q, queries) {
        ll b, i;
        // cost of switch
        tie(b, i) = q;
        FOR (cnt, MAX_CNT) {
            FOR (l, n) {
                rv[i] = min(rv[i], dist[l][m - 1][cnt] + cnt * b);
            }
        }
    }

    FOR (i, t) {
        cout << rv[i] << '\n';
    }

    return 0;
}