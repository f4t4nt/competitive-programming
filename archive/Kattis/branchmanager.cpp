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

void dfs(ll v, ll &rv, vector<vector<ll>> &children, vector<ll> &d, vector<bool> &visited) {
    visited[v] = true;
    
    if (sz(children[v]) == 0) {
        while (rv < sz(d) && visited[d[rv]]) {
            rv++;
        }
    } else {
        FORE (c, children[v]) {
            dfs(c, rv, children, d, visited);
        }
    }

    visited[v] = false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> children(n);
    FOR (i, n - 1) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        children[a].pb(b);
    }
    FORE (c, children) {
        ssort(c);
    }
    vector<ll> d(m);
    FOR (i, m) {
        cin >> d[i];
        d[i]--;
    }

    ll rv = 0;
    vector<bool> visited(n);
    dfs(0, rv, children, d, visited);
    cout << rv << '\n';

    return 0;
}