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

    ll n, q; cin >> n;
    vector<tuple<ll, ll, ll>> items(n);
    FOR (i, n) {
        ll p, v; cin >> p >> v;
        items[i] = {v, -p, i};
    }
    cin >> q;
    vector<tuple<ll, ll, ll>> queries(q);
    FOR (i, q) {
        ll x, k; cin >> x >> k;
        queries[i] = {x, k, i};
    }
    ssort(items);
    ssort(queries);
    vector<vector<ll>> rv(q);
    ll cur = 0;
    set<pair<ll, ll>> active;
    for (auto [x, k, i] : queries) {
        while (cur < n && get<0>(items[cur]) <= x) {
            active.insert({get<1>(items[cur]), get<2>(items[cur])});
            cur++;
        }
        while (sz(active) > 10) {
            active.erase(prev(active.end()));
        }
        if (sz(active)) {
            FORE (p, active) {
                rv[i].pb(p.second + 1);
            }
        } else {
            rv[i].pb(-1);
        }
    }
    FORE (v, rv) {
        FORE (p, v) cout << p << ' ';
        cout << '\n';
    }

    return 0;
}