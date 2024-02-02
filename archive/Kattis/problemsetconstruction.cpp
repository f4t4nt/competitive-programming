#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#include <bits/extc++.h>
using namespace __gnu_pbds;

using indexed_set = tree<
    pair<ll, ll>,
    null_type,
    less<pair<ll, ll>>,
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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k, tt; cin >> n >> k >> tt;
    vector<tuple<ll, ld, ll>> qs(n);
    FOR (i, n) {
        ld p; ll s; cin >> p >> s;
        qs[i] = {s, p, i};
    }
    vector<ld> rv(n);
    ssort(qs);
    vector<vector<ld>> dp(k + 1, vector<ld>(tt + 1));
    dp[0][0] = 1;
    FOR (i, n) {
        auto [s0, p0, idx] = qs[i];
        FORR (t, tt) {
            for (ll j = min(i, k - 1); j >= 0 && j + (n - i) >= k; j--) {
                if (dp[j][t] == 0) continue;
                ld p = dp[j][t], c = (ld) (k - j) / (n - i);
                dp[j][t] = p * (1 - c);
                dp[j + 1][t] += p * c * (1 - p0);
                if (t + s0 <= tt) {
                    dp[j + 1][t + s0] += p * c * p0;
                    rv[idx] += p * c * p0;
                }
            }
        }
    }
    FOR (i, n) {
        cout << fixed << setprecision(10) << rv[i] * n / k << '\n';
    }

    return 0;
}