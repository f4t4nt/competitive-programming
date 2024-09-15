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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m; cin >> n >> m;
    vector<pll> deg(n), cur(n, {1, 0});
    FOR (i, n) deg[i].s = cur[i].s = i;
    FOR (i, m) {
        ll u, v; cin >> u >> v;
        deg[u].f++, deg[v].f++;
    }
    ssort(deg);
    ll rem = n - 2;
    FOR (i, n) {
        if (rem == 0) break;
        ll j = deg[i].s;
        ll want = deg[i].f - cur[j].f;
        if (want > rem) {
            cur[j].f += rem;
            rem = 0;
        } else {
            cur[j].f += want;
            rem -= want;
        }
    }
    ll err = 0;
    FOR (i, n) {
        ll j = deg[i].s;
        err += cur[j].f != deg[i].f;
    }
    cout << err << '\n' << n << ' ' << n - 1 << '\n';
    rsort(cur);
    // root
    ll idx = 1;
    FOR (_, cur[0].f) cout << cur[0].s << ' ' << cur[idx++].s << '\n';
    // others
    FOB (i, 1, n) FOR (_, cur[i].f - 1) cout << cur[i].s << ' ' << cur[idx++].s << '\n';

    return 0;
}