#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef complex<ld> cd;
typedef pair<ld, ld> pld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

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
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    vector<ll> _a(n), a;
    for (ll &x : _a) cin >> x;
    a.pb(_a[0]);
    for (ll i = 1; i < n; i++)
        if (_a[i] != _a[i - 1]) a.pb(_a[i]);
    n = sz(a);
    vector<ll> nxt_gt(n, n), prv_gt(n, -1);
    stack<pll> stk;
    for (ll i = 0; i < n; i++) {
        while (!stk.empty() && stk.top().f < a[i]) {
            nxt_gt[stk.top().s] = i;
            stk.pop();
        }
        stk.push({a[i], i});
    }
    stk = stack<pll>();
    for (ll i = n - 1; i >= 0; i--) {
        while (!stk.empty() && stk.top().f < a[i]) {
            prv_gt[stk.top().s] = i;
            stk.pop();
        }
        stk.push({a[i], i});
    }
    vector<vector<ll>> adj(n);
    for (ll i = 0; i < n; i++) {
        if (prv_gt[i] != -1) adj[prv_gt[i]].pb(i);
        if (nxt_gt[i] != n) adj[nxt_gt[i]].pb(i);
    }
    vector<ll> dp(n, -1);
    auto dfs = [&](auto&& self, ll u) -> ll {
        if (dp[u] != -1) return dp[u];
        dp[u] = 0;
        for (ll v : adj[u]) 
            dp[u] = max(dp[u], self(self, v) + 1);
        return dp[u];
    };
    for (ll i = 0; i < n; i++)
        if (dp[i] == -1) dfs(dfs, i);
    cout << *max_element(all(dp)) + 1 << '\n';

    return 0;
}
