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
    ll,
    null_type,
    less<ll>,
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
// #define f first
// #define s second

#define FOR(x, e) for (ll x = 0; x < (ll)e; x++)
#define FOR1(x, e) for (ll x = 1; x < (ll)e; x++)
#define FORR(x, e) for (ll x = (ll)e - 1; x >= 0; x--)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

void dfs(ll u, ll p, ll &ans, str &ref, str &stk, vector<vector<ll>> &adj) {
    ch cur = ref[u];
    if (cur == '(' || cur == '[' || cur == '{') {
        stk.pb(cur);
    } elif (cur == ')' && !stk.empty() && stk.back() == '(') {
        stk.pop_back();
    } elif (cur == ']' && !stk.empty() && stk.back() == '[') {
        stk.pop_back();
    } elif (cur == '}' && !stk.empty() && stk.back() == '{') {
        stk.pop_back();
    } else {
        return;
    }
    if (stk.empty()) {
        ans++;
    }
    for (ll v : adj[u]) {
        if (v != p) {
            dfs(v, u, ans, ref, stk, adj);
        }
    }
    if (cur == '(' || cur == '[' || cur == '{') {
        stk.pop_back();
    } elif (cur == ')') {
        stk.pb('(');
    } elif (cur == ']') {
        stk.pb('[');
    } elif (cur == '}') {
        stk.pb('{');
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    str ref; cin >> ref;
    vector<vector<ll>> adj(n);
    FOR (i, n - 1) {
        ll u, v; cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    ll ans = 0;
    str stk;
    FOR (i, n) {
        stk.clear();
        dfs(i, -1, ans, ref, stk, adj);
    }
    cout << ans << '\n';

    return 0;
}