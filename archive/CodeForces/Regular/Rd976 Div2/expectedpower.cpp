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

struct DSU {
    ll cnt; vector<ll> e;
    DSU(ll n) : cnt(n), e(n, -1) {}
    void reset() { e = vector<ll>(sz(e), -1); cnt = sz(e); }
    ll get(ll x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool same_set(ll a, ll b) { return get(a) == get(b); }
    ll size(ll x) { return -e[get(x)]; }
    bool unite(ll x, ll y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y]; e[y] = x;
        cnt--;
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        vector<tuple<ll, ll, ll>> operations(m);
        map<pair<ll, ll>, vector<tuple<ll, ll, ll>>> dr_intervals;
        FOR (idx, m) {
            ll a, d, k;
            cin >> a >> d >> k;
            ll r = (a + d - 1) % d + 1;
            ll s = (a - r) / d;
            ll e = s + k;
            dr_intervals[{d, r}].pb({s, e, idx});
            operations[idx] = make_tuple(a, d, k);
        }
        DSU dsu(m);
        ll tot = 0;
        for (auto &dr_pair : dr_intervals) {
            auto &intervals = dr_pair.second;
            ssort(intervals);
            vector<pll> merged;
            auto [prv_s, prv_e, prv] = intervals[0];
            FOR1 (i, sz(intervals)) {
                auto [s, e, idx] = intervals[i];
                if (s <= prv_e + 1) {
                    dsu.unite(prv, idx);
                    prv_e = max(prv_e, e);
                } else {
                    tot += prv_e - prv_s + 1;
                    merged.pb({prv_s, prv_e});
                    prv_s = s;
                    prv_e = e;
                    prv = idx;
                }
            }
            tot += prv_e - prv_s + 1;
            merged.pb({prv_s, prv_e});
        }
        set<ll> roots;
        FOR (i, m) roots.insert(dsu.get(i));
        ll ans = sz(roots) + n - tot;
        cout << ans << '\n';
    }

    return 0;
}