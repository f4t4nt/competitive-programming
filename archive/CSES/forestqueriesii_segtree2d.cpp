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
#define x first
#define y second

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

struct SegTree2D {
    ll n, m; vector<vector<ll>> data, raw0;

    SegTree2D(ll n, ll m, vector<vector<ll>>& raw) : n(n), m(m), data(4 * n, vector<ll>(4 * m)), raw0(raw) {
        build_x(1, 0, n-1);
    }

    void build_y(ll vx, ll lx, ll rx, ll vy, ll ly, ll ry) {
        if (ly == ry) {
            if (lx == rx) data[vx][vy] = raw0[lx][ly];
            else data[vx][vy] = data[vx*2][vy] + data[vx*2+1][vy];
        } else {
            ll my = (ly + ry) / 2;
            build_y(vx, lx, rx, vy*2, ly, my);
            build_y(vx, lx, rx, vy*2+1, my+1, ry);
            data[vx][vy] = data[vx][vy*2] + data[vx][vy*2+1];
        }
    }

    void build_x(ll vx, ll lx, ll rx) {
        if (lx != rx) {
            ll mx = (lx + rx) / 2;
            build_x(vx*2, lx, mx);
            build_x(vx*2+1, mx+1, rx);
        }
        build_y(vx, lx, rx, 1, 0, m-1);
    }

    ll qry_y(ll vx, ll vy, ll tly, ll try_, ll ly, ll ry) {
        if (ly > ry) return 0;
        if (ly == tly && try_ == ry) return data[vx][vy];
        ll tmy = (tly + try_) / 2;
        return qry_y(vx, vy*2, tly, tmy, ly, min(ry, tmy))
             + qry_y(vx, vy*2+1, tmy+1, try_, max(ly, tmy+1), ry);
    }

    ll qry_x(ll vx, ll tlx, ll trx, ll lx, ll rx, ll ly, ll ry) {
        if (lx > rx) return 0;
        if (lx == tlx && trx == rx) return qry_y(vx, 1, 0, m-1, ly, ry);
        ll tmx = (tlx + trx) / 2;
        return qry_x(vx*2, tlx, tmx, lx, min(rx, tmx), ly, ry)
             + qry_x(vx*2+1, tmx+1, trx, max(lx, tmx+1), rx, ly, ry);
    }

    void upd_y(ll vx, ll lx, ll rx, ll vy, ll ly, ll ry, ll x, ll y, ll new_val) {
        if (ly == ry) {
            if (lx == rx) data[vx][vy] = new_val;
            else data[vx][vy] = data[vx*2][vy] + data[vx*2+1][vy];
        } else {
            ll my = (ly + ry) / 2;
            if (y <= my) upd_y(vx, lx, rx, vy*2, ly, my, x, y, new_val);
            else upd_y(vx, lx, rx, vy*2+1, my+1, ry, x, y, new_val);
            data[vx][vy] = data[vx][vy*2] + data[vx][vy*2+1];
        }
    }

    void upd_x(ll vx, ll lx, ll rx, ll x, ll y, ll new_val) {
        if (lx != rx) {
            ll mx = (lx + rx) / 2;
            if (x <= mx) upd_x(vx*2, lx, mx, x, y, new_val);
            else upd_x(vx*2+1, mx+1, rx, x, y, new_val);
        }
        upd_y(vx, lx, rx, 1, 0, m-1, x, y, new_val);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n, q; cin >> n >> q;
    vector<str> grid(n);
    FOR (i, n) cin >> grid[i];
    vector<vector<ll>> raw(n, vector<ll>(n));
    FOR (i, n) FOR (j, n) raw[i][j] = grid[i][j] == '*';
    SegTree2D st(n, n, raw);
    while (q--) {
        ll t; cin >> t;
        if (t == 1) {
            ll x, y; cin >> x >> y; --x, --y;
            st.upd_x(1, 0, n-1, x, y, 1 - raw[x][y]);
            raw[x][y] = 1 - raw[x][y];
        } else {
            ll x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2; --x1, --y1, --x2, --y2;
            cout << st.qry_x(1, 0, n-1, x1, x2, y1, y2) << '\n';
        }
    }

    return 0;
}