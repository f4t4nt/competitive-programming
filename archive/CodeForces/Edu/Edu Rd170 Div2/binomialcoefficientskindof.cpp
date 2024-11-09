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
#define x first
#define y second

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

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    vector<ll> n(t), k(t);
    FOR (i, t) cin >> n[i];
    FOR (i, t) cin >> k[i];
    // ll N = 20;
    // vector<vector<ll>> tmp(N, vector<ll>(N));
    // FOR (i, N) {
    //     tmp[i][0] = tmp[i][i] = 1;
    //     FOR1 (k, i) {
    //         tmp[i][k] = (tmp[i][k - 1] + tmp[i - 1][k - 1]) % MOD;
    //     }
    // }
    // FOR (i, N) {
    //     FOR (j, i + 1) {
    //         cout << tmp[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
    vector<ll> pow2(1e5 + 1);
    pow2[0] = 1;
    FOR1 (i, 1e5 + 1) pow2[i] = (pow2[i - 1] * 2) % MOD;
    FOR (i, t) cout << (k[i] == 0 || k[i] == n[i] ? 1 : pow2[k[i]]) << '\n';

    return 0;
}