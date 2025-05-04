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

template<typename T>
using indexed_set = tree<
    T,
    null_type,
    less<T>,
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

// #ifdef LOCAL
// #include "tester.cpp"
// #define main test_main
// extern istringstream fin;
// extern ostringstream fout;
// string test_file_name = "tests";
// #define cin fin
// #define cout fout
// #endif

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<vector<ll>> adj(n);
        for (ll i = 1; i < n; i++) {
            ll u, v; cin >> u >> v; u--, v--;
            adj[u].pb(v), adj[v].pb(u);
        }
        vector<ll> ans(n);
        cout << "? 1 1 1" << endl;
        cin >> ans[0];
        if (abs(ans[0]) == 1) {
            for (ll i = 1; i < n; i++) {
                cout << "? 1 1 " << i + 1 << endl;
                cin >> ans[i];
                ans[i] -= ans[0];
            }
        } else {
            if (ans[0] != 0) {
                ans[0] /= -2;
                cout << "? 2 1" << endl;
            }
            for (ll i = 1; i < n; i++) {
                cout << "? 1 1 " << i + 1 << endl;
                cin >> ans[i];
            }
            if (ans[0] == 0) {
                cout << "? 2 1" << endl;
                cout << "? 1 1 1" << endl;
                cin >> ans[0];
                ans[0] /= 2;
            }
        }
        cout << "! ";
        for (ll x : ans) cout << x << ' ';
        cout << endl;
    }

    return 0;
}