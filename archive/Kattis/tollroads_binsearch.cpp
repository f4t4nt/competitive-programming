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

struct DSU {
	vector<ll> e;
	DSU(ll n) { e = vector<ll>(n, -1); }
    void reset() { e = vector<ll>(sz(e), -1); }
	ll get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool same_set(ll a, ll b) { return get(a) == get(b); }
	ll size(ll x) { return -e[get(x)]; }
	bool unite(ll x, ll y) {
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
		return true;
	}
};

// void binsearch(ll &n, ll &m, ll lo, ll hi,
//     ll dsu_idx,
//     DSU &dsu,
//     vector<tuple<ll, ll, ll>> &edges,
//     vector<pair<ll, ll>> &rv,
//     set<tuple<ll, ll, ll>> &queries) {
//     if (lo >= hi) {
//         return;
//     }
//     if (queries.empty()) {
//         return;
//     }
//     ll mid = (lo + hi) / 2;
//     while (dsu_idx < m && get<0>(edges[dsu_idx]) <= mid) {
//         dsu.unite(get<1>(edges[dsu_idx]), get<2>(edges[dsu_idx]));
//         dsu_idx++;
//     }
//     set<tuple<ll, ll, ll>> lo_queries;
//     FORE (query, queries) {
//         ll u, v, i;
//         tie(u, v, i) = query;
//         if (dsu.same_set(u, v)) {
//             rv[i] = {mid, dsu.size(u)};
//             lo_queries.insert(query);
//         }
//     }
//     FORE (query, lo_queries) {
//         queries.erase(query);
//     }
//     DSU lo_dsu(n);
//     binsearch(n, m, lo, mid, 0, lo_dsu, edges, rv, lo_queries);
//     binsearch(n, m, mid + 1, hi, dsu_idx, dsu, edges, rv, queries);
// }

vector<tuple<ll, ll, ll>> kruskal(ll n, ll m, DSU dsu, vector<tuple<ll, ll, ll>> &edges) {
    vector<tuple<ll, ll, ll>> mst;
    FOR (i, m) {
        ll u, v, t;
        tie(t, u, v) = edges[i];
        if (dsu.unite(u, v)) {
            mst.pb({t, u, v});
        }
    }
    return mst;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, q, min_t = 2e5, max_t = 0;
    cin >> n >> m >> q;
    vector<tuple<ll, ll, ll>> edges(m);
    FOR (i, m) {
        ll u, v, t;
        cin >> u >> v >> t;
        u--, v--;
        edges[i] = {t, u, v};
        min_t = min(min_t, t);
        max_t = max(max_t, t);
    }
    ssort(edges);

    vector<tuple<ll, ll, ll>> queries(q);
    FOR (i, q) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        queries[i] = {u, v, i};
    }

    // vector<tuple<ll, ll, ll>> mst = kruskal(n, m, DSU(n), edges);

    DSU dsu(n);
    vector<pair<ll, ll>> rv(q), bounds(q, {min_t, max_t});
    vector<pair<ll, ll>> queries_bin(q);
    while (true) {
        ll cnt = 0;
        FOR (i, q) {
            if (bounds[i].first > bounds[i].second) {
                continue;
            }
            queries_bin[cnt] = {(bounds[i].first + bounds[i].second) / 2, i};
            cnt++;
        }
        if (cnt == 0) {
            break;
        }
        sort(queries_bin.begin(), queries_bin.begin() + cnt);
        ll dsu_idx = 0;
        dsu.reset();
        FOR (i, cnt) {
            ll bound, idx;
            tie(bound, idx) = queries_bin[i];
            while (dsu_idx < sz(edges) && get<0>(edges[dsu_idx]) <= bound) {
                dsu.unite(get<1>(edges[dsu_idx]), get<2>(edges[dsu_idx]));
                dsu_idx++;
            }
            ll u, v, q_idx;
            tie(u, v, q_idx) = queries[idx];
            if (dsu.same_set(u, v)) {
                rv[q_idx] = {bound, dsu.size(u)};
                bounds[idx].second = bound - 1;
            } else {
                bounds[idx].first = bound + 1;
            }
        }
    }

    FOR (i, q) {
        cout << rv[i].first << ' ' << rv[i].second << '\n';
    }

    return 0;
}