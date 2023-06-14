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

vector<ll> get_factors(ll n) {
    vector<ll> factors;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            factors.pb(i);
            if (i * i != n) {
                factors.pb(n / i);
            }
        }
    }
    return factors;
}

void gen(ll v, vector<ll> &par, vector<vector<ll>> &adj) {
    FORE (u, adj[v]) {
        if (u != par[v]) {
            par[u] = v;
            gen(u, par, adj);
        }
    }
}

void dfs(ll v,
    vector<ll> &a,
    vector<ll> &par,
    vector<vector<ll>> &dp,
    vector<vector<ll>> &factors,
    vector<vector<ll>> &adj)
{
    FORE (u, adj[v]) {
        if (u != par[v]) {
            dfs(u, a, par, dp, factors, adj);
            FOB (i, 2, 1e4 + 1) {
                dp[v][i] += dp[u][i];
            }
        }
    }
    FOB (i, 2, 1e4 + 1) {
        if (a[v] != i) {
            dp[v][i] += i;
        }
    }
    // FOB (i, 2, 1e4 + 1) {
    for (ll i = 1e4; i >= 2; i--) {
        FORE (j, factors[i]) {
            if (j == 1) {
                continue;
            }
            dp[v][j] = min(dp[v][j], dp[v][i]);
        }
        for (ll j = 2 * i; j <= 1e4; j += i) {
            dp[v][j] = min(dp[v][j], dp[v][i]);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vector<vector<ll>> factors(1e4 + 1);
    FOB(i, 1, 1e4 + 1) {
        factors[i] = get_factors(i);
    }

    ll n;
    cin >> n;
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

    vector<ll> par(n, -1);
    gen(0, par, adj);
    vector<vector<ll>> dp(n, vector<ll>(1e4 + 1));

    dfs(0, a, par, dp, factors, adj);

    ll rv = 1e18;
    FOB (i, 2, 1e4 + 1) {
        rv = min(rv, dp[0][i]);
    }
    cout << rv << '\n';

    return 0;
}