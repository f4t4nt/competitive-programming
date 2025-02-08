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

struct PairData {
    ll x, y;
    ll dir;
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> a(n), b(n);
        FOR (i, n) cin >> a[i];
        FOR (i, n) cin >> b[i];
        vector<PairData> pairs(n);
        FOR (i, n) {
            if (a[i] <= b[i]) {
                pairs[i].x = a[i];
                pairs[i].y = b[i];
                pairs[i].dir = 0;
            } else {
                pairs[i].x = b[i];
                pairs[i].y = a[i];
                pairs[i].dir = 1;
            }
        }
        sort(all(pairs), [&](auto &a, auto &b){
            if(a.x != b.x) return a.x < b.x;
            return a.y < b.y;
        });
        bool ok = true;
        FOR1 (i, n) {
            if (pairs[i].y < pairs[i - 1].y) {
                ok = false;
                break;
            }
        }
        if (!ok) {
            cout << "NO\n";
            continue;
        }
        vector<vector<ll>> top(n), bot(n);
        FOR (i, n) {
            top[i] = {pairs[i].x, pairs[i].y};
            bot[i] = {pairs[i].y, pairs[i].x};
        }
        vector<vector<vector<bool>>> dp(n + 1, vector<vector<bool>>(2, vector<bool>(2)));
        vector<vector<vector<ll>>> top_val(n + 1, vector<vector<ll>>(2, vector<ll>(2))),
            bot_val = top_val;
        FOR (o, 2) {
            ll flip = (pairs[0].dir == o ? 0 : 1);
            ll p = flip % 2;
            dp[1][o][p] = true;
            top_val[1][o][p] = top[0][o];
            bot_val[1][o][p] = bot[0][o];
        }
        FOR1 (i, n) {
            FOR (o_cur, 2) {
                ll flip_cur = (pairs[i].dir == o_cur ? 0 : 1);
                FOR (o_prev, 2) {
                    FOR (par_prev, 2) {
                        if (!dp[i][o_prev][par_prev]) continue;
                        ll prev_top = top_val[i][o_prev][par_prev];
                        ll prev_bot = bot_val[i][o_prev][par_prev];
                        ll cur_top = top[i][o_cur];
                        ll cur_bot = bot[i][o_cur];
                        if (cur_top >= prev_top && cur_bot >= prev_bot) {
                            ll par_cur = par_prev ^ flip_cur;
                            dp[i + 1][o_cur][par_cur] = true;
                            if (dp[i + 1][o_cur][par_cur]) {
                                top_val[i + 1][o_cur][par_cur] = cur_top;
                                bot_val[i + 1][o_cur][par_cur] = cur_bot;
                            }
                        }
                    }
                }
            }
        }
        ok = false;
        FOR (o, 2) {
            if (dp[n][o][0]) {
                ok = true;
                break;
            }
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }

    return 0;
}