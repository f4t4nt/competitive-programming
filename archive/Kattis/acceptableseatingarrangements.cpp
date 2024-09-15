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

ll r, c;
vector<pair<pll, pll>> ans;
vector<vector<ll>> cur, dst;

bool try_swap(pll src, pll dst, vector<pll> &pos) {
    if (src == dst) return true;
    ll src_val = cur[src.f][src.s], dst_val = cur[dst.f][dst.s];
    ll src_prv = -1, src_nxt = 1e9, dst_prv = -1, dst_nxt = 1e9;
    if (src.s > 0) src_prv = cur[src.f][src.s - 1];
    if (src.s < c - 1) src_nxt = cur[src.f][src.s + 1];
    if (dst.s > 0) dst_prv = cur[dst.f][dst.s - 1];
    if (dst.s < c - 1) dst_nxt = cur[dst.f][dst.s + 1];
    if (!(src_prv < dst_val && dst_val < src_nxt &&
          dst_prv < src_val && src_val < dst_nxt)) return false;
    swap(cur[src.f][src.s], cur[dst.f][dst.s]);
    swap(pos[src_val], pos[dst_val]);
    ans.pb({src, dst});
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> r >> c;
    cur.resize(r, vector<ll>(c)), dst = cur;
    vector<pll> cur_pos(r * c), dst_pos = cur_pos;
    FOR (i, r) FOR (j, c) {
        cin >> cur[i][j]; cur[i][j]--;
        cur_pos[cur[i][j]] = {i, j};
    }
    FOR (i, r) FOR (j, c) {
        cin >> dst[i][j]; dst[i][j]--;
        dst_pos[dst[i][j]] = {i, j};
    }
    FOR (i, r * c) {
        auto [x, y] = cur_pos[i];
        while (!try_swap(cur_pos[i], dst_pos[i], cur_pos)) {
            y = cur_pos[i].s;
            while (y < c && !try_swap({x, y}, dst_pos[i], cur_pos)) y++;
        }
    }
    cout << sz(ans) << '\n';
    FORE (x, ans)
        cout << x.f.f + 1 << ' ' << x.f.s + 1 << ' '
            << x.s.f + 1 << ' ' << x.s.s + 1 << '\n';

    return 0;
}