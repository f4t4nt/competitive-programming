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

// https://open.kattis.com/problems/tollroads

constexpr ll MAX_D = 20;

struct DSU {
    ll cnt;
	vector<ll> e;
	DSU(ll n) { e = vector<ll>(n, -1); cnt = n; }
	ll get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool same_set(ll a, ll b) { return get(a) == get(b); }
	ll size(ll x) { return -e[get(x)]; }
    ll count() { return cnt; }
	bool unite(ll x, ll y) {
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
        cnt--;
		return true;
	}
};

ll gen_tree(ll u, ll d, vector<vector<ll>> &children, vector<ll> &depth, vector<ll> &subtree_size) {
    depth[u] = d;
    FORE (v, children[u]) {
        subtree_size[u] += gen_tree(v, d + 1, children, depth, subtree_size);
    }
    return subtree_size[u];
}

pair<ll, ll> jump(ll u, ll d, vector<vector<pair<ll, ll>>> &ancestors) {
    ll t = 0;
    FOR (i, MAX_D) {
        if ((d >> i) & 1) {
            t = max(ancestors[u][i].second, t);
            u = ancestors[u][i].first;
        }
    }
    return {u, t};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, q;
    cin >> n >> m >> q;
    vector<tuple<ll, ll, ll>> edges(m);
    FOR (i, m) {
        ll u, v, t;
        cin >> u >> v >> t;
        u--, v--;
        edges[i] = {t, u, v};
    }
    ssort(edges);

    DSU dsu(n);
    vector<pair<ll, ll>> parent(n, {-1, -1});
    vector<map<ll, ll>> sizes(n);
    vector<vector<ll>> children(n);
    FOR (i, m) {
        ll u, v, t;
        tie(t, u, v) = edges[i];
        ll u_leader = dsu.get(u), v_leader = dsu.get(v);
        if (u_leader != v_leader) {
            if (dsu.e[u_leader] > dsu.e[v_leader]) {
                swap(u_leader, v_leader);
            }
            dsu.e[u_leader] += dsu.e[v_leader];
            assert(parent[v_leader].first == -1);
            dsu.e[v_leader] = u_leader;
            parent[v_leader] = {u_leader, t};
            children[u_leader].pb(v_leader);
            sizes[u_leader][t] = -dsu.e[u_leader];
            dsu.cnt--;
        }
    }

    ll root = 0;
    while (parent[root].first != -1) {
        root++;
    }
    parent[root] = {root, 0};
    vector<ll> depth(n), subtree_sz(n, 1);
    gen_tree(root, 0, children, depth, subtree_sz);
    vector<vector<pair<ll, ll>>> ancestors(n, vector<pair<ll, ll>>(MAX_D));
    FOR (i, n) {
        ancestors[i][0] = parent[i];
    }
    FOB (i, 1, MAX_D) {
        FOR (v, n) {
            ancestors[v][i] = ancestors[ancestors[v][i - 1].first][i - 1];
        }
    }

    while (q--) {
        ll a, b, lca, t;
        cin >> a >> b;
        a--, b--;
        if (depth[a] < depth[b]) {
            swap(a, b);
        }
        tie(a, t) = jump(a, depth[a] - depth[b], ancestors);
        if (a != b) {
            FORR (i, 20) {
                ll a2 = ancestors[a][i].first, b2 = ancestors[b][i].first;
                if (a2 != b2) {
                    a = a2, b = b2;
                    t = max(max(ancestors[a][i].second, ancestors[b][i].second), t);
                }
            }
            lca = ancestors[a][0].first;
            t = max(max(ancestors[a][0].second, ancestors[b][0].second), t);
        } else {
            lca = a;
        }
        cout << t << ' ' << sizes[lca][t] << '\n';
    }

    return 0;
}