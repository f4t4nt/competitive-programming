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

ll dx[] = {0, 0, 1, -1};
ll dy[] = {1, -1, 0, 0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, m; cin >> n >> m;
    vector<str> raw(n);
    FOR (i, n) cin >> raw[i];
    vector<str> blownup(2 * n + 1, str(2 * m + 1, '.'));
    FOR (i, n) FOR (j, m) if (raw[i][j] != '.') blownup[2 * i + 1][2 * j + 1] = raw[i][j];
    for (ll i = 0; i <= 2 * n; i += 2) {
        for (ll j = 0; j <= 2 * m; j += 2) {
            if (i > 0 && j > 0 && blownup[i - 1][j - 1] == '\\') blownup[i][j] = '#';
            if (i > 0 && j < 2 * m && blownup[i - 1][j + 1] == '/') blownup[i][j] = '#';
            if (i < 2 * n && j > 0 && blownup[i + 1][j - 1] == '/') blownup[i][j] = '#';
            if (i < 2 * n && j < 2 * m && blownup[i + 1][j + 1] == '\\') blownup[i][j] = '#';
        }
    }
    map<pll, ll> ids;
    ids[{-1, -1}] = 0;
    FOR (i, 2 * n + 1) FOR (j, 2 * m + 1) if (blownup[i][j] == '.') ids[{i, j}] = sz(ids);
    // cout << "ids size: " << sz(ids) << '\n';
    DSU dsu(sz(ids));
    FOR (i, 2 * n + 1) FOR (j, 2 * m + 1) {
        if (blownup[i][j] != '.') continue;
        // cout << "i: " << i << " j: " << j << '\n';
        bool ok = false;
        if (i == 0 || j == 0 || i == 2 * n || j == 2 * m) {
            // cout << "united " << i << ' ' << j << " with " << -1 << ' ' << -1 << '\n';
            ok = true;
            dsu.unite(0, ids[{i, j}]);
        }
        FOR (k, 4) {
            ll ni = i + dx[k], nj = j + dy[k];
            if (ni < 0 || nj < 0 || ni > 2 * n || nj > 2 * m) continue;
            if (blownup[ni][nj] == '.') {
                // cout << "united " << i << ' ' << j << " with " << ni << ' ' << nj << '\n';
                ok = true;
                dsu.unite(ids[{i, j}], ids[{ni, nj}]);
            }
        }
        // cout << "dsu.cnt: " << dsu.cnt << '\n';
    }
    cout << dsu.cnt - 1 << '\n';
    // FOR (i, 2 * n + 1) cout << blownup[i] << '\n';

    return 0;
}