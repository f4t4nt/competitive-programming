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
        ll n, mx = 0; cin >> n;
        vector<ll> a(n);
        for (ll &ai : a) {
            cin >> ai;
            mx = max(mx, ai);
        }
        ssort(a);
        vector<ll> ref(mx + 1, 1e18);
        for (ll i = 0; i < n; i++) ref[a[i]] = i;
        for (ll i = mx - 1; i >= 0; i--)
            if (ref[i] == 1e18) ref[i] = ref[i + 1];  
        vector<tuple<ll, ll, ll>> edges;
        for (ll i = 0; i < n; i++) {
            if (i < n - 1) {
                edges.pb({a[i + 1] - a[i], i, i + 1});
                if (a[i] == a[i + 1]) continue;
            }
            // ll j = i;
            for (ll x = 2 * a[i]; x <= mx; x += a[i]) {
                // j = lower_bound(a.begin() + j, a.end(), x) - a.begin();
                // edges.pb({a[j] - x, i, j});
                ll j = ref[x];
                edges.pb({a[j] - x, i, j});
            }
        }
        ssort(edges);
        DSU dsu(n);
        ll ans = 0;
        for (auto [w, u, v] : edges) {
            if (dsu.unite(u, v)) ans += w;
        }
        cout << ans << '\n';
    }

    return 0;
}