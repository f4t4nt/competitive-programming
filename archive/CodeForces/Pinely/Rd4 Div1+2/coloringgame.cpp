#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef complex<long double> cd;
typedef long double ld;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pld,
    null_type,
    less<pld>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#pragma GCC target("popcnt,lzcnt")

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

bool eval(vector<vector<ll>> &ref, vector<vector<ll>> &adj, vector<ll> &assgn, ll u, ll c) {
    if (assgn[u] == c) return true;
    if (assgn[u] == 1 - c) return false;
    assgn[u] = c;
    ref[c].pb(u);
    for (ll v : adj[u]) if (!eval(ref, adj, assgn, v, 1 - c)) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        vector<vector<ll>> adj(n), ref(2);
        FOR (i, m) {
            ll u, v; cin >> u >> v;
            u--, v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        vector<ll> assgn(n, -1);
        if (!eval(ref, adj, assgn, 0, 0)) {
            cout << "Alice" << endl;
            FOR (i, n) {
                cout << "1 2" << endl;
                ll j, c; cin >> j >> c;
            }
        } else {
            cout << "Bob" << endl;
            FOR (i, n) {
                ll a, b; cin >> a >> b;
                a--, b--;
                if (a > b) swap(a, b);
                if (a == 0 && sz(ref[0])) {
                    cout << ref[0].back() + 1 << " 1" << endl;
                    ref[0].pop_back();
                } elif ((a == 1 || b == 1) && sz(ref[1])) {
                    cout << ref[1].back() + 1 << " 2" << endl;
                    ref[1].pop_back();
                } else {
                    ll x = rng() & 1;
                    while (true) {
                        if (sz(ref[x])) {
                            cout << ref[x].back() + 1 << " 3" << endl;
                            ref[x].pop_back();
                            break;
                        }
                        x = 1 - x;
                    }
                }
            }
        }
    }
    
    return 0;
}