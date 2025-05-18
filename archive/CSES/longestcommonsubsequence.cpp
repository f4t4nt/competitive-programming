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

    ll n, m; cin >> n >> m;
    vector<ll> a(n), b(m);
    for (ll &x : a) cin >> x;
    for (ll &x : b) cin >> x;
    vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0));
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= m; j++) {
            ll tmp = dp[i - 1][j - 1];
            if (a[i - 1] == b[j - 1]) tmp++;
            dp[i][j] = max({
                dp[i - 1][j],
                tmp,
                dp[i][j - 1]
            });
        }
    }
    vector<ll> ans;
    ll i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            ans.pb(a[i - 1]);
            i--, j--;
        } elif (dp[i][j] == dp[i - 1][j]) i--;
        elif (dp[i][j] == dp[i][j - 1]) j--;
        else assert(false);
    }
    cout << dp[n][m] << '\n';
    flip(ans);
    for (ll x : ans) cout << x << ' ';
    cout << '\n';

    return 0;
}
