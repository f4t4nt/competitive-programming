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

#ifdef LOCAL
#include "tester.cpp"
#define main test_main
extern istringstream fin;
extern ostringstream fout;
string test_file_name = "tests";
#define cin fin
#define cout fout
#endif

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    vector<pair<ll, pll>> pq_all, pq_single;

    for (ll sum = 0; sum <= 5e4; sum++) {
        for (ll x = 0; x <= sum; x++) {
            ll y = sum - x;
            ll tx = x * 3 + 1, ty = y * 3 + 1;
            if (sz(pq_all) < 1e6) {
                pq_all.pb({tx + ty, {tx, ty}});
                pq_all.pb({tx + ty + 1, {tx, ty + 1}});
                pq_all.pb({tx + ty + 1, {tx + 1, ty}});
                pq_all.pb({tx + ty + 4, {tx + 1, ty + 1}});
            }
            if (sz(pq_single) < 1e6) {
                pq_single.pb({tx + ty, {tx, ty}});
            } else break;
        }
        if (sz(pq_single) >= 1e6) break;
    }

    ssort(pq_all);
    ssort(pq_single);

    ll q; cin >> q;
    while (q--) {
        ll n; cin >> n;
        vector<ll> t(n);
        ll i_all = 0, i_single = 0;
        vector<pll> ans;
        set<pll> used;
        for (ll &ti : t) {
            cin >> ti;
            if (ti == 1) {
                while (i_all < sz(pq_all)) {
                    auto [sum, p] = pq_all[i_all++];
                    if (used.find(p) == used.end()) {
                        ans.pb(p);
                        used.insert(p);
                        break;
                    }
                }
            } else {
                while (i_single < sz(pq_single)) {
                    auto [sum, p] = pq_single[i_single++];
                    if (used.find(p) == used.end()) {
                        ans.pb(p);
                        used.insert(p);
                        break;
                    }
                }
            }
        }
        for (auto &[x, y] : ans) cout << x << ' ' << y << '\n';
    }

    return 0;
}