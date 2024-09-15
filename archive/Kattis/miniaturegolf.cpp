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

ll get_score(ll h, ll k, vector<ll> &pre, ll kdx) {
    return pre[kdx] + (h - kdx) * k;
}

ll bash(ll k, vector<ll> scores) {
    ll tot = 0;
    FORE (x, scores) tot += min(x, k);
    return tot;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll p, h; cin >> p >> h;
    vector<vector<ll>> scores(p, vector<ll>(h)), pre(p, {0});
    ll mx = 0;
    FOR (i, p) {
        FOR (j, h) {
            cin >> scores[i][j];
            mx = max(mx, scores[i][j]);
        }
        ssort(scores[i]);
        FOR (j, h) pre[i].pb(pre[i].back() + scores[i][j]);
    }
    vector<ll> ans(p, p), ans2 = ans;
    FOR (i, p) {
        // map<ll, ll> ref;
        // FOR (j, p) {
        //     FOR (k, mx + 1) {
        //         auto my_tmp = scores[i],
        //             his_tmp = scores[j];
        //         FORE (x, my_tmp) x = min(x, k);
        //         FORE (x, his_tmp) x = min(x, k);
        //         ll my_total = accumulate(all(my_tmp), 0LL),
        //             his_total = accumulate(all(his_tmp), 0LL);
        //         if (his_total <= my_total) ref[k]++;
        //     }
        // }
        // for (auto &[k, v] : ref) {
        //     ans[i] = min(ans[i], v);
        // }
        // map<ll, ll> diff;
        // ll prv = 0;
        // for (auto &[k, v] : ref) {
        //     diff[k] = v - prv;
        //     prv = v;
        // }
        map<ll, ll> diff2;
        diff2[0] = p;
        set<ll> my_cutoffs(all(scores[i]));
        FOR (j, p) {
            if (i == j) continue;
            ll idx = 0, jdx = 0;
            set<ll> cutoffs = my_cutoffs;
            FORE (x, scores[j]) cutoffs.insert(x);
            cutoffs.insert(1e18);
            bool prv_beat = true;
            auto nxt_x = cutoffs.begin();
            FORE (x, cutoffs) {
                if (x == 1e18) break;
                nxt_x++;
                while (idx < h && scores[i][idx] <= x) idx++;
                while (jdx < h && scores[j][jdx] <= x) jdx++;
                // ll my_score = get_score(h, x, pre[i], idx),
                //     his_score = get_score(h, x, pre[j], jdx);
                // bool cur_beat = his_score <= my_score;
                // if (prv_beat && !cur_beat) diff2[x]--;
                // if (cur_beat && !prv_beat) diff2[x]++;
                // prv_beat = cur_beat;
                ll my_score = pre[i][idx],
                    my_slope = h - idx,
                    his_score = pre[j][jdx],
                    his_slope = h - jdx;
                if (my_slope == his_slope) continue;
                ld inter_x_ld = (ld)(his_score - my_score) / (my_slope - his_slope);
                if (inter_x_ld < x - 3) continue;
                if (prv_beat) {
                    // previously his_score <= my_score
                    // we only change when my_score < his_score
                    ll inter_x = (ll)inter_x_ld - 5;
                    while (my_score + my_slope * inter_x >=
                        his_score + his_slope * inter_x && inter_x <= *nxt_x) inter_x++;
                    if (inter_x > *nxt_x || inter_x <= x) continue;
                    diff2[inter_x]--;
                } else {
                    // previously my_score < his_score
                    // we only change when his_score <= my_score
                    ll inter_x = (ll)inter_x_ld - 5;
                    while (my_score + my_slope * inter_x <
                        his_score + his_slope * inter_x && inter_x <= *nxt_x) inter_x++;
                    if (inter_x > *nxt_x || inter_x <= x) continue;
                    diff2[inter_x]++;
                }
                prv_beat = !prv_beat;
            }
        }
        ll cur = 0;
        for (auto &[k, v] : diff2) {
            cur += v;
            ans2[i] = min(ans2[i], cur);
        }
    }
    // FOR (i, p) cout << ans[i] << '\n';
    FOR (i, p) cout << ans2[i] << '\n';

    return 0;
}