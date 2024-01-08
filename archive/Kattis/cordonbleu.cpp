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
    tree_order_statistics_node_update
>;

#pragma GCC target("popcnt,lzcnt")

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

#define x first
#define y second

const ll INF = 1e9;

ll get_dist(pair<ll, ll> a, pair<ll, ll> b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

vector<ll> hungarian(vector<vector<ll>> &costs) {
    ll J = sz(costs), W = sz(costs[0]); // J <= W
    vector<ll> job(W + 1, -1), ys(J), yt(W + 1), rv;
    FOR (j_cur, J) {
        ll w_cur = W;
        job[w_cur] = j_cur;
        vector<ll> min_to(W + 1, INF), prev(W + 1, -1);
        vector<bool> in_Z(W + 1);
        while (job[w_cur] != -1) {
            in_Z[w_cur] = true;
            ll j = job[w_cur], del = INF, w_nxt;
            FOR (w, W) {
                if (!in_Z[w]) {
                    if (min_to[w] > costs[j][w] - ys[j] - yt[w]) {
                        min_to[w] = costs[j][w] - ys[j] - yt[w];
                        prev[w] = w_cur;
                    }
                    if (del > min_to[w]) {
                        del = min_to[w];
                        w_nxt = w;
                    }
                }
            }
            FOR (w, W + 1) {
                if (in_Z[w]) ys[job[w]] += del, yt[w] -= del;
                else min_to[w] -= del;
            }
            w_cur = w_nxt;
        }
        for (ll w; w_cur != W; w_cur = w) job[w_cur] = job[w = prev[w_cur]];
        rv.pb(-yt[W]);
    }
    return rv;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    vector<pair<ll, ll>> dst(n), src(m + 1);
    FOR (i, n) cin >> dst[i].x >> dst[i].y;
    FOR (i, m + 1) cin >> src[i].x >> src[i].y;
    vector<vector<ll>> dists(n, vector<ll>(n + m - 1));
    FOR (i, n) {
        FOR (j, m + 1) dists[i][j] = get_dist(dst[i], src[j]) + get_dist(dst[i], src[m]);
        FOB (j, m + 1, n + m - 1) dists[i][j] = dists[i][m];
    }
    vector<ll> rv = hungarian(dists);
    cout << rv[n - 1] << '\n';

    return 0;
}