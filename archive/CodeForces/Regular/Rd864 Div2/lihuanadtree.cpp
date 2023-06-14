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

void dfs(ll v, ll &n,
    vector<ll> &par,
    vector<ll> &sze,
    vector<ll> &imp,
    vector<ll> &a,
    vector<set<pair<ll, ll>>> &ref,
    vector<vector<ll>> &adj)
{
    sze[v] = 1;
    imp[v] = a[v];
    FORE (u, adj[v]) {
        if (u != par[v]) {
            par[u] = v;
            dfs(u, n, par, sze, imp, a, ref, adj);
            sze[v] += sze[u];
            imp[v] += imp[u];
            ref[v].insert({-sze[u], u});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> q;
    vector<ll> a(n);
    FOR (i, n) {
        cin >> a[i];
    }
    vector<vector<ll>> adj(n);
    FOR (i, n - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<set<pair<ll, ll>>> ref(n);
    vector<ll> par(n, -1), sze(n), imp(n);
    dfs(0, n, par, sze, imp, a, ref, adj);

    while (q--) {
        ll t, x;
        cin >> t >> x;
        x--;
        if (t == 1) {
            cout << imp[x] << '\n';
        } else {
            if (ref[x].empty()) {
                continue;
            }
            auto it = ref[x].begin();
            ll y = it->second, p = par[x];
            assert(ref[p].count({-sze[x], x}));
            ref[p].erase({-sze[x], x});
            assert(ref[x].count({-sze[y], y}));
            ref[x].erase({-sze[y], y});
            imp[x] -= imp[y];
            sze[x] -= sze[y];
            imp[y] += imp[x];
            sze[y] += sze[x];
            ref[p].insert({-sze[y], y});
            ref[y].insert({-sze[x], x});
            par[x] = y;
            par[y] = p;
        }
    }

    return 0;
}