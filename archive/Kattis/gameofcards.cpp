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
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, k, xr = 0;
    cin >> n >> k;
    vector<vector<ll>> a(n), nim(n);
    FOR (i, n) {
        ll m;
        cin >> m;
        a[i].resize(m), nim[i].resize(m);
        FOR (j, m) cin >> a[i][j];
    }
    FOR (i, n) {
        FOR (j, sz(a[i])) {
            bitset<1001> ok;
            FOR (x, min(j, k + 1)) {
                ll y = j - x;
                if (y >= a[i][y]) {
                    y -= a[i][y];
                    ok[nim[i][y]] = 1;
                } elif (y + 1 == a[i][y]) ok[0] = 1;
            }
            while (ok[nim[i][j]]) nim[i][j]++;
        }
        xr ^= nim[i].back();
    }
    cout << (xr ? "Alice can win." : "Bob will win.") << '\n';

    return 0;
}