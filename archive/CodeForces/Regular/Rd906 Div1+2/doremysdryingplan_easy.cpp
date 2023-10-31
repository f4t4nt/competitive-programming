#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;
 
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

// imma show YOU how great i am.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n, m, k;
        cin >> n >> m >> k;
        vector<pair<ll, ll>> ranges(m);
        vector<vector<ll>> events(n + 1);
        FOR (i, m) {
            ll l, r;
            cin >> l >> r;
            l--;
            ranges[i] = {l, r};
            events[l].pb(2 * i);
            events[r].pb(2 * i + 1);
        }
        vector<ll> cnt(m);
        set<ll> active;
        ll base = -1;
        map<set<ll>, ll> pair_cnts;
        FOR (i, n + 1) {
            FORE (e, events[i]) {
                if (e % 2 == 0) {
                    active.insert(e / 2);
                } else {
                    active.erase(e / 2);
                }
            }
            if (sz(active) == 0) {
                base++;
            } elif (sz(active) == 1) {
                cnt[*active.begin()]++;
            } elif (sz(active) == 2) {
                pair_cnts[active]++;
            }
        }
        vector<ll> cnt_ = cnt;
        rsort(cnt_);
        ll rv = cnt_[0] + cnt_[1];
        FORE (e, pair_cnts) {
            set<ll> tmp = e.first;
            ll pair_cnt = e.second;
            ll a = *tmp.begin(),
                b = *tmp.rbegin();
            rv = max(rv, cnt[a] + cnt[b] + pair_cnt);
        }
        cout << base + rv << '\n';
    }

    return 0;
}