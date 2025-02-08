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

struct TwoSat {
    ll n; vector<vector<ll>> qr;
    vector<ll> values; // 0: false, 1: true
    vector<ll> val, comp, z; ll time = 0;
    TwoSat(ll n) : n(n), qr(2 * n) {}
    void either(ll f, ll j) {
        f = max(2 * f, -1 - 2 * f);
        j = max(2 * j, -1 - 2 * j);
        qr[f].pb(j ^ 1);
        qr[j].pb(f ^ 1);
    }
    void set_value(ll x) { either(x, x); }
    void at_most_one(const vector<ll>& li) {
        if (sz(li) < 2) return;
        ll cur = ~li[0];
        for (ll i = 2; i < sz(li); i++) {
            ll next = li[i];
            ll v = n++;
            either(cur, ~v);
            either(next, ~v);
            cur = ~v;
        }
        either(cur, ~li[1]);
    }
    ll dfs(ll i) {
        ll low = val[i] = ++time, x; z.pb(i);
        for (ll j : qr[i]) if (!comp[j]) low = min(low, val[j] ?: dfs(j));
        if (low == val[i]) do {
            x = z.back(); z.pop_back();
            comp[x] = low;
            if (values[x >> 1] == -1) values[x >> 1] = x & 1;
        } while (x != i);
        return val[i] = low;
    }
    bool solve() {
        values.assign(n, -1); val.assign(2 * n, 0); comp = val;
        FOR (i, 2 * n) if (!comp[i]) dfs(i);
        FOR (i, n) if (comp[2 * i] == comp[2 * i + 1]) return 0;
        return 1;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, r, l; cin >> n >> r >> l;
    vector<pll> lamps(l);
    FOR (i, l) cin >> lamps[i].f >> lamps[i].s;
    TwoSat ts(l);
    FOR (i, l) FOR (j, i) {
        if (lamps[i].f == lamps[j].f) {
            if (abs(lamps[i].s - lamps[j].s) <= 2 * r) {
                ts.at_most_one({i, j});
            }
        }
        if (lamps[i].s == lamps[j].s) {
            if (abs(lamps[i].f - lamps[j].f) <= 2 * r) {
                ts.at_most_one({~i, ~j});
            }
        }
    }
    cout << (ts.solve() ? "YES" : "NO") << '\n';

    return 0;
}