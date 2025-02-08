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
// #define x first
// #define y second

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

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while(t--) {
        ll n, m, k; cin >> n >> m >> k;
        vector<ll> a(n), b(m);
        ll sum_a = 0;
        FOR (i, n) {
            cin >> a[i];
            sum_a += a[i];
        }
        FOR (j, m) cin >> b[j];
        if (k == 0) {
            cout << sum_a << '\n';
            continue;
        }
        ll CNT = 1 << m;
        vector<ll> mask(CNT), cost(CNT);
        mask[0] = 0xFFFFFFFFu;
        FOR1 (x, CNT) {
            ll j = __builtin_ctz(x);
            ll y = x ^ (1 << j);
            mask[x] = mask[y] & b[j];
            cost[x] = cost[y] + 1;
        }
        vector<vector<ll>> best(n, vector<ll>(m + 1)), dval = best;
        FOR (i, n) {
            ll ai = a[i];
            FOR (x, CNT) {
                ll c = cost[x], tmp = ai & mask[x];
                ll inc = ai - tmp;
                if (inc > best[i][c]) {
                    best[i][c] = inc;
                }
            }
            for (ll c = 1; c <= m; c++) {
                if (best[i][c] < best[i][c - 1]) {
                    best[i][c] = best[i][c - 1];
                }
            }
            dval[i][0] = 0;
            for (ll c = 1; c <= m; c++) {
                if (c == 1) {
                    dval[i][c] = best[i][1];
                } else {
                    dval[i][c] = best[i][c] - best[i][c - 1];
                }
            }
        }
        vector<ll> used(n);
        std::priority_queue<pll> pq;
        FOR (i, n) {
            if (m >= 1) {
                ll val = dval[i][1];
                if (val > 0) {
                    pq.push({val, i});
                }
            }
        }
        ll tot = 0, cur_cost = 0;
        while (!pq.empty() && cur_cost < k) {
            auto [val, idx] = pq.top(); pq.pop();
            tot += val;
            cur_cost++;
            ll ci = ++used[idx];
            if (ci < m) {
                ll nxt = dval[idx][ci + 1];
                if (nxt > 0) {
                    pq.push({nxt, idx});
                }
            }
        }
        ll ans = sum_a - tot;
        cout << ans << '\n';
    }

    return 0;
}