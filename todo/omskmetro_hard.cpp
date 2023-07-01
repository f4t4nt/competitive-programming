#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ch = char;
using str = string;

#define pb push_back
#define elif else if
#define sz(C) (ll) C.size()
#define all(C) C.begin(), C.end()
#define flip(C) reverse(all(C))
#define ssort(C) sort(all(C))
#define rsort(C) sort(all(C), greater<>())

#define FOR(x, e) for(ll x = 0; x < (ll) e; x++)
#define FORR(x, e) for(ll x = (ll) e - 1; x >= 0; x--)
#define FOB(x, b, e) for(auto x = b; x < e; x++)
#define FORE(x, C) for(auto &x : C)

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

// https://codeforces.com/contest/1843/problem/F2

ll get_lca(ll u, ll v, vector<ll> &depth, vector<vector<ll>> &par) {
    if (depth[u] < depth[v]) swap(u, v);
    FORR (i, 20) if (depth[par[u][i]] >= depth[v]) u = par[u][i];
    if (u == v) return u;
    FORR (i, 20) if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
    return par[u][0];
}

// return last idx such that segs[idx][0] <= depth
vector<ll> get_seg(ll depth, vector<vector<ll>> &segs) {
    ll lo = 0, hi = sz(segs) - 1;
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;
        if (segs[mid][0] <= depth) lo = mid;
        else hi = mid - 1;
    }
    return segs[lo];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll q;
        cin >> q;
        vector<ll> depth = {0};
        // bin jump table, [i][j] = 2^jth parent of i
        vector<vector<ll>> par = {vector<ll>(20, 0)},
        // [0] = cur min, [1] = min start idx, [2] = cur max, [3] = max start idx
            cur = {{0, 0, 1, 0}};
        // [0] = min segs, [1] = max segs
        vector<vector<vector<vector<ll>>>> maxx = { // vertex 0
                { // min/max 1
                    { // list of strictly increasing mins 2 [sum, idx]
                        {0, 0}
                    },
                    { // list of strictly decreasing maxs 2 [sum, idx]
                        {1, 0}
                    }
                }
            };
        while (q--) {
            ch c;
            cin >> c;
            if (c == '+') {
                ll p, x;
                cin >> p >> x;
                p--;
                ll q = sz(par);
                par.pb(par[p]);
                par[q][0] = p;
                FOB (i, 1, 20) par[q][i] = par[par[q][i - 1]][i - 1];
                depth.pb(depth[p] + 1);
                cur.pb(cur[p]);
                cur[q][0] = cur[q][0] + x;
                if (cur[q][0] > 0) {
                    cur[q][0] = 0;
                    cur[q][1] = depth[q];
                }
                cur[q][2] = cur[q][2] + x;
                if (cur[q][2] < 0) {
                    cur[q][2] = 0;
                    cur[q][3] = depth[q];
                }
                maxx.pb(maxx[p]);
                while (!maxx[q][0].empty() && maxx[q][0].back()[0] >= cur[q][0]) maxx[q][0].pop_back();
                maxx[q][0].pb({cur[q][0], cur[q][1]});
                while (!maxx[q][1].empty() && maxx[q][1].back()[0] <= cur[q][2]) maxx[q][1].pop_back();
                maxx[q][1].pb({cur[q][2], cur[q][3]});
            } else {
                ll u, v, k;
                cin >> u >> v >> k;
                u--, v--;
                ll lca = get_lca(u, v, depth, par);
                // first decreasing segment between lca and u
                auto u0 = get_seg(depth[lca], maxx[u][0]),
                // first increasing segment between lca and u
                    u1 = get_seg(depth[lca], maxx[u][1]),
                // first decreasing segment between lca and v
                    v0 = get_seg(depth[lca], maxx[v][0]),
                // first increasing segment between lca and v
                    v1 = get_seg(depth[lca], maxx[v][1]);
                cout << "wtf\n";
            }
        }
        cout << "Done\n";
    }

    return 0;
}