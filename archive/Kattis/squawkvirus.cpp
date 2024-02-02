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


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   
    cout.tie(nullptr);

    ll n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<ll> vals(n, 0);
    vals[s] = 1;
    ll cur = 1;

    vector<vector<ll>> adj(n, vector<ll>());

    FOR (i, m) {
        ll a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    FOR (i, t) {
        vector<ll> new_vals(n, 0);
        ll new_cur = 0;
        
        FOR (a, n) {
            FORE (b, adj[a]) {
                new_vals[b] += vals[a];
                new_cur += vals[a];
            }
        }

        cur = new_cur;
        vals = new_vals;
    }

    cout << cur << '\n';

    return 0;
}