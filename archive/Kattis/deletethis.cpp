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

    ll w, h, n, m; cin >> w >> h >> n >> m;
    vector<ll> x0(n), y0(n), x1(m), y1(m);
    vector<bool> ok(n);
    map<ll, ll> x_map, y_map;
    FOR (i, n) {
        cin >> x0[i] >> y0[i];
        x_map[x0[i]] = 0;
        y_map[y0[i]] = 0;
        ok[i] = ((x0[i] <= w - 8) && (y0[i] <= h - 4));
    }
    FOR (i, m) {
        cin >> x1[i] >> y1[i];
        x_map[x1[i]] = 0;
        y_map[y1[i]] = 0;
    }
    if (n == 0) {
        cout << 0 << '\n';
        return 0;
    }
    x_map[-1e18] = 0;
    y_map[-1e18] = 0;
    x_map[1e18] = 0;
    y_map[1e18] = 0;
    ll x_cnt = 0, y_cnt = 0;
    FORE (p, x_map) p.second = x_cnt++;
    FORE (p, y_map) p.second = y_cnt++;
    vector<vector<ll>> grid0(x_cnt, vector<ll>(y_cnt)), grid1 = grid0;
    FOR (i, n) {
        x0[i] = x_map[x0[i]];
        y0[i] = y_map[y0[i]];
        grid0[x0[i]][y0[i]] = 1;
    }
    FOR (i, m) {
        x1[i] = x_map[x1[i]];
        y1[i] = y_map[y1[i]];
        grid1[x1[i]][y1[i]] = 1;
    }
    FOB (i, 1, x_cnt) FOB (j, 1, y_cnt) {
        grid0[i][j] += grid0[i - 1][j] + grid0[i][j - 1] - grid0[i - 1][j - 1];
        grid1[i][j] += grid1[i - 1][j] + grid1[i][j - 1] - grid1[i - 1][j - 1];
    }
    ll rv = LLONG_MAX;
    multiset<ll> xs, ys;
    FOR (a, n) {
        if (!ok[a]) continue;
        xs.insert(x0[a]);
        ys.insert(y0[a]);
        FOB (b, a, n) {
            if (!ok[b]) continue;
            xs.insert(x0[b]);
            ys.insert(y0[b]);
            FOB (c, b, n) {
                if (!ok[c]) continue;
                xs.insert(x0[c]);
                ys.insert(y0[c]);
                FOB (d, c, n) {
                    if (!ok[d]) continue;
                    xs.insert(x0[d]);
                    ys.insert(y0[d]);

                    ll x_min = *xs.begin() - 1, x_max = *xs.rbegin();
                    ll y_min = *ys.begin() - 1, y_max = *ys.rbegin();
                    ll in1 = grid1[x_max][y_max] - grid1[x_min][y_max] - grid1[x_max][y_min] + grid1[x_min][y_min],
                        out0 = n - (grid0[x_max][y_max] - grid0[x_min][y_max] - grid0[x_max][y_min] + grid0[x_min][y_min]);
                    rv = min(rv, in1 + out0);
                        

                    xs.erase(xs.find(x0[d]));
                    ys.erase(ys.find(y0[d]));
                }
                xs.erase(xs.find(x0[c]));
                ys.erase(ys.find(y0[c]));
            }
            xs.erase(xs.find(x0[b]));
            ys.erase(ys.find(y0[b]));
        }
        xs.erase(xs.find(x0[a]));
        ys.erase(ys.find(y0[a]));
    }
    cout << rv << '\n';

    return 0;
}