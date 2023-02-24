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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, rv = 0;
    cin >> n;
    vector<pair<ll, ll>> ref(n);
    vector<vector<pair<ll, ll>>> adj(n);
    FOR (i, n - 1) {
        ll u, v, p;
        cin >> u >> v >> p;
        adj[u].pb({v, p});
        adj[v].pb({u, p});
        ref[u].first = max(ref[u].first, p);
        ref[u].second += p;
        ref[v].first = max(ref[v].first, p);
        ref[v].second += p;
        rv += p;
    }

    FOR (i, n) {
        if (ref[i].first * 2 > ref[i].second) {
            rv -= ref[i].second - ref[i].first;
        } else {
            rv -= ref[i].second / 2;
        }
    }

    cout << rv << '\n';

    return 0;
}