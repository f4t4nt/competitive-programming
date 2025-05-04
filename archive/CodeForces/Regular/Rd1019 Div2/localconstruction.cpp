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
#define sz(C) (ll)C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())
#define f first
#define s second

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

vector<ll> top_sort(vector<vector<ll>> &adj, vector<ll> &deg) { // deg is in-degree
    ll n = sz(adj);
    vector<ll> ord; queue<ll> q;
    for (ll i = 0; i < n; i++)
        if (deg[i] == 0) q.push(i);
    while (!q.empty()) {
        ll u = q.front(); q.pop();
        ord.pb(u);
        for (ll v : adj[u])
            if (--deg[v] == 0) q.push(v);
    }
    return ord;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, mx = 0; cin >> n;
        vector<ll> a(n);
        for (ll &ai : a) {
            cin >> ai;
            mx = max(mx, ai);
        }
        vector<pll> rem;
        for (ll i = 0; i < n; i++) {
            if (a[i] == -1) a[i] = ++mx;
            rem.pb({a[i], i});
        }
        vector<ll> deg(n);
        vector<vector<ll>> adj(n);
        for (ll lvl = 1; lvl < mx; lvl++) {
            vector<pll> rem_new;
            bool up = !(lvl & 1);
            ll i = 0;
            while (i + 1 < sz(rem) && rem[i].f == lvl) {
                ll u = rem[i].s, v = rem[i + 1].s;
                if (!up) swap(u, v);
                adj[u].pb(v);
                deg[v]++;
                i++;
            }
            rem_new.pb(rem[i]);
            i++;
            while (i < sz(rem)) {
                bool tmp = up;
                if (rem[i].f == lvl) tmp = !tmp;
                else rem_new.pb(rem[i]);
                ll u = rem[i - 1].s, v = rem[i].s;
                if (!tmp) swap(u, v);
                adj[u].pb(v);
                deg[v]++;
                i++;
            }
            rem = rem_new;
        }
        auto ord = top_sort(adj, deg);
        vector<ll> ans(n);
        for (ll i = 0; i < n; i++)
            ans[ord[i]] = i + 1;
        for (ll &ai : ans) cout << ai << ' ';
        cout << '\n';
    }

    return 0;
}