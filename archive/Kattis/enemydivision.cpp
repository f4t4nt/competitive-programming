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

void dfs(ll u, vector<bool> &vis, vector<ll> &assignments, vector<vector<ll>> &enem) {
    if (vis[u]) {
        return;
    }
    vis[u] = true;
    ll cnt = 0;
    FORE (v, enem[u]) {
        cnt += (assignments[v] == assignments[u]);
    }
    if (cnt > 1) {
        assignments[u] = 1 - assignments[u];
        FORE (v, enem[u]) {
            if (assignments[v] == assignments[u]) {
                dfs(v, vis, assignments, enem);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> enem(n);
    FOR (i, m) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        enem[a].pb(b);
        enem[b].pb(a);
    }
    bool ok = true;
    FOR (i, n) {
        if (sz(enem[i]) > 1) {
            ok = false;
            break;
        }
    }
    if (ok) {
        cout << 1 << '\n';
        FOR (i, n) {
            cout << i + 1 << ' ';
        }
        cout << '\n';
        return 0;
    }
    vector<ll> assignments(n);
    FOR (i, n) {
        vector<bool> vis(n);
        dfs(i, vis, assignments, enem);
    }
    vector<vector<ll>> teams(2);
    FOR (i, n) {
        teams[assignments[i]].pb(i);
    }
    cout << 2 << '\n';
    FORE (team, teams) {
        FORE (i, team) {
            cout << i + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}