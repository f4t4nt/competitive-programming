#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef char ch;
typedef string str;
typedef pair<ll, ll> pll;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define ssort(C) sort(all(C))

#define FOR(x, e) for (ll x = 0; x < (ll) e; x++)

struct TwoSat {
    ll N;
    vector<vector<ll>> gr;
    vector<ll> values;

    TwoSat(int n = 0) : N(n), gr(2*n) {}

    ll addVar() {
        gr.emplace_back();
        gr.emplace_back();
        return N++;
    }

    void either(ll f, ll j) {
        f = max(2 * f, -1-2*f);
        j = max(2*j, -1-2*j);
        gr[f].pb(j^1);
        gr[j].pb(f^1);
    }

    void setValue(ll x) {either(x,x);}

    vector<ll> val, comp, z; ll time = 0;
    ll dfs(ll i) {
        ll low = val[i] = ++time, x; z.pb(i);
        for (ll e : gr[i]) if (!comp[e])
            low = min(low, val[e] ?: dfs(e));
        if (low == val[i]) do {
            x = z.back(); z.pop_back();
            comp[x] = low;
            if (values[x>>1] == -1)
                values[x>>1] = x&1;
        } while (x != i);
        return val[i] = low;
    }

    bool solve() {
        values.assign(N, -1);
        val.assign(2*N, 0); comp = val;
        FOR (i, 2*N) if (!comp[i]) dfs(i);
        FOR (i, N) if (comp[2*i] == comp[2*i+1]) return 0;
        return 1;
    }
};

void dfs(ll u, vector<ll> &par, vector<vector<ll>> &adj) {
    for (ll v : adj[u]) {
        if (par[v] == -1) {
            par[v] = u;
            dfs(v, par, adj);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t;
    cin >> t;

    while (t--) {
        ll n;
        cin >> n;

        vector<ll> color(2 * n);
        vector<vector<ll>> shows(n);
        TwoSat sat0(2 * n);

        FOR (i, 2 * n) {
            cin >> color[i];
            color[i]--;
            shows[color[i]].pb(i);
        }

        FOR (i, n) {
            sat0.either(shows[i][0], shows[i][1]);
            sat0.either(~shows[i][0], ~shows[i][1]);
        }

        vector<vector<ll>> adj(2 * n, vector<ll>());
        FOR (i, 2 * n - 1) {
            ll u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }

        bool res = false;
        for (auto& root : shows[0]) {
            vector<ll> par(2 * n, -1);
            TwoSat ts = sat0;
            par[root] = root;
            dfs(root, par, adj);
            FOR (i, 2 * n) {
                if (i == root) continue;
                ts.either(~i, par[i]);
            }

            ll val = ts.solve();
            if (val) {
                res = true;
                FOR (i, 2 * n) {
                    if (ts.values[i]) {
                        cout << i + 1 << " ";
                    }
                }
                cout << "\n";
                break;
            }
        }

        if (!res) {
            cout << "-1\n";
        }
    }

    return 0;
}