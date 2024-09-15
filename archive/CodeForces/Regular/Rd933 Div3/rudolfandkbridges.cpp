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
#define FOB(x, b, e) for (auto x = b; x < e; x++)
#define FORE(x, C) for (auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

ll single_row(vector<ll> &depth, ll m, ll d) {
    vector<ll> dp(m, LLONG_MAX);
    dp[0] = 1;
    std::priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({1, 0});
    FOB (i, 1, m) {
        while (pq.top().s < i - d - 1) pq.pop();
        dp[i] = pq.top().f + depth[i] + 1;
        pq.push({dp[i], i});
    }
    return dp[m - 1];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m, k, d; cin >> n >> m >> k >> d;
        vector<vector<ll>> depth(n, vector<ll>(m));
        FOR (i, n) FOR (j, m) cin >> depth[i][j];
        ll ans, sum = 0;
        deque<ll> dq;
        FOR (i, k) {
            ll cur = single_row(depth[i], m, d);
            sum += cur;
            dq.pb(cur);
        }
        ans = sum;
        FOB (i, k, n) {
            ll cur = single_row(depth[i], m, d);
            sum -= dq.front();
            dq.pop_front();
            sum += cur;
            dq.pb(cur);
            ans = min(ans, sum);
        }
        cout << ans << '\n';
    }

    return 0;
}