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

const ll MOD = 1e9 + 9;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll k, b; cin >> k >> b;
    vector<vector<ll>> f(b + 1, vector<ll>(k)), c = f;
    c[0][0] = 1;
    FOR (i, b) {
        FOR (j, k) {
            c[i + 1][(2 * j) % k] = (c[i + 1][(2 * j) % k] + c[i][j]) % MOD;
            c[i + 1][(2 * j + 1) % k] = (c[i + 1][(2 * j + 1) % k] + c[i][j]) % MOD;
            f[i + 1][(2 * j) % k] = (f[i + 1][(2 * j) % k] + f[i][j]) % MOD;
            f[i + 1][(2 * j + 1) % k] = (f[i + 1][(2 * j + 1) % k] + f[i][j] + c[i][j]) % MOD;
        }
    }
    cout << f[b][0] << '\n';

    return 0;
}