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

// https://open.kattis.com/problems/gowithflow

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    ll n; cin >> n;
    pll best = {0, 0};
    ll mn = 0, tot = 0;
    vector<ll> lens(n);
    FOR (i, n) {
        str w; cin >> w;
        lens[i] = sz(w);
        mn = max(mn, lens[i]);
        tot += lens[i];
    }
    tot += n;
    FOB (len, mn, tot) {
        ll cnt = 0, cursor = 0, cur = 0, nxt = 1e18;
        vector<vector<ll>> doc(n, vector<ll>(len, -1));
        FOR (idx, n) {
            if (len - cursor < lens[idx]) {
                if (cursor > 0 && doc[cnt][cursor - 1] == 0)
                    doc[cnt][cursor - 1] = -1;
                nxt = min(nxt, cursor + lens[idx]);
                cursor = 0;
                cnt++;
            }
            ll end_w = cursor + lens[idx];
            FOR (i, lens[idx]) doc[cnt][cursor++] = end_w;
            if (cursor < len) doc[cnt][cursor++] = 0;
        }
        cnt++;
        if (cnt <= best.s) break;
        vector<ll> dp0(len), dp1(len);
        // FOR (i, len) if (!doc[0][i] &&
        //                 (i > 0 && doc[0][i - 1]) &&
        //                 (i + 1 < len && doc[0][i + 1]))
        //     dp0[i] = cur = 1;
        {
            ll i = 0;
            while (i < len && i != -1) {
                if (!doc[0][i]) dp0[i++] = cur = 1;  
                if (i == len) break;              
                i = doc[0][i];
            }
        }
        FOB (i, 1, cnt) {
            // FOR (j, len) {
            //     if (!doc[i][j] &&
            //         (j > 0 && doc[i][j - 1]) &&
            //         (j + 1 < len && doc[i][j + 1])) {
            //         FOB (k, -1, 2) {
            //             if (j + k >= 0 && j + k < len) {
            //                 dp1[j] = max(dp1[j], dp0[j + k] + 1);
            //                 cur = max(cur, dp1[j]);
            //             }
            //         }
            //     }
            // }
            ll j = 0;
            while (j < len && j != -1) {
                if (!doc[i][j]) {
                    FOB (k, -1, 2) {
                        if (j + k >= 0 && j + k < len) {
                            dp1[j] = max(dp1[j], dp0[j + k] + 1);
                            cur = max(cur, dp1[j]);
                        }
                    }
                    j++;
                }
                if (j == len) break;
                j = doc[i][j];
            }
            dp0 = dp1;
            dp1 = vector<ll>(len);
        }
        if (cur > best.s) best = {len, cur};
        len = nxt - 1;
    }
    cout << best.f << ' ' << best.s << '\n';

    return 0;
}