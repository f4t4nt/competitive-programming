#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using db = double;
using cd = complex<double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
    rb_tree_tag,
    tree_order_statistics_node_update
>;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FORE(x, C) for(auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

int solution(vector<int> &a) {
    ll n = sz(a);
    vector<vector<int>> dp(4, vector<int>(n + 2, -1e9));
    dp[0] = vector<int>(n + 2, 0);
    FOR (i, n) {
        FOR (j, 3) {
            dp[j + 1][i + 2] = max(dp[j + 1][i + 2], dp[j + 1][i + 1]);
            dp[j + 1][i + 2] = max(dp[j + 1][i + 2], dp[j][i] + a[i]);
        }
    }
    return dp[3][n + 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    FORE (v, a) cin >> v;
    cout << solution(a) << '\n';

    return 0;
}