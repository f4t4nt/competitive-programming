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

struct SegTree {
    ll n; vector<tuple<ll, ll, ll>> data;
    SegTree (ll n, vector<ll> &raw) : n(n), data(4 * n)
        { build(raw); }
    tuple<ll, ll, ll> build(vector<ll> &raw, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (r - l == 1) return data[i] = {raw[l], raw[l], 0};
        ll m = (l + r) / 2;
        auto lo = build(raw, 2 * i, l, m),
            hi = build(raw, 2 * i + 1, m, r);
        return data[i] = {min(get<0>(lo), get<0>(hi)),
                max(get<1>(lo), get<1>(hi)),
                max({
                    get<2>(lo),
                    get<2>(hi),
                    get<1>(hi) - get<0>(lo)
                })
            };
    }
    void updi(ll ui, ll val, ll i = 1, ll l = 0, ll r = -1) {
        if (r == -1) r = n;
        if (r - l == 1) { data[i] = {val, val, 0}; return; }
        ll m = (l + r) / 2;
        if (ui < m) updi(ui, val, 2 * i, l, m);
        else updi(ui, val, 2 * i + 1, m, r);
        auto &lo = data[2 * i], &hi = data[2 * i + 1];
        data[i] = {min(get<0>(lo), get<0>(hi)),
                max(get<1>(lo), get<1>(hi)),
                max({
                    get<2>(lo),
                    get<2>(hi),
                    get<1>(hi) - get<0>(lo)
                })
            };
    }
    ll qry() {
        return get<2>(data[1]);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll t; cin >> t;
    while (t--) {
        ll n, q; cin >> n >> q;
        vector<ll> a(n), b(n);
        FOR (i, n) {
            cin >> a[i];
            ll ii = n - i - 1;
            b[ii] = a[i] - ii;
            a[i] -= i;
        }
        SegTree sta(n, a), stb(n, b);
        // cout << sta.qry() << ' ' << stb.qry() << '\n';
        cout << max(sta.qry(), stb.qry()) << '\n';
        while (q--) {
            ll p, x; cin >> p >> x; p--;
            ll pp = n - p - 1;
            a[p] = x - p;
            sta.updi(p, a[p]);
            b[pp] = x - pp;
            stb.updi(pp, b[pp]);
            // cout << sta.qry() << ' ' << stb.qry() << '\n';
            cout << max(sta.qry(), stb.qry()) << '\n';
        }
    }

    return 0;
}