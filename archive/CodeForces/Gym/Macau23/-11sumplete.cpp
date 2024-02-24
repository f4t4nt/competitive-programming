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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n; cin >> n;
    vector<str> raw(n);
    FOR(i, n) cin >> raw[i];
    vector<ll> row_sum0(n), col_sum0(n);
    FOR (i, n) cin >> row_sum0[i];
    FOR (i, n) cin >> col_sum0[i];
    auto row_sum = row_sum0, col_sum = col_sum0;
    FOR (i, n) FOR (j, n) if (raw[i][j] == '-') {
        row_sum[i]++;
        col_sum[j]++;
    }
    bool ok = true;
    vector<vector<ll>> ref(n, vector<ll>(n));
    vector<pll> cur_cols;
    FOR (i, n) cur_cols.pb({col_sum[i], i});
    FOR (i, n) {
        rsort(cur_cols);
        FOR (k, min(n, row_sum[i])) {
            auto [_, j] = cur_cols[k];
            ref[i][j] = 1;
            cur_cols[k].first--;
        }
    }
    FOR (i, n) ok &= cur_cols[i].first == 0;
    cout << (ok ? "Yes" : "No") << '\n';
    if (ok) {
        FOR(i, n) {
            FOR (j, n) {
                if (raw[i][j] == '-') cout << !ref[i][j];
                else cout << ref[i][j];
            }
            cout << '\n';
        }
    }

    return 0;
}