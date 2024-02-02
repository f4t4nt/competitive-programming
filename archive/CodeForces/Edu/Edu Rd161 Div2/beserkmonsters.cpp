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

    ll t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<ll> att(n), def(n), cur_hp(n), rv(n);
        FOR (i, n) cin >> att[i];
        FOR (i, n) cin >> def[i];
        set<ll> cur;
        set<pair<ll, ll>> hps;
        FOR (i, n) {
            cur_hp[i] = def[i];
            if (i > 0) cur_hp[i] -= att[i - 1];
            if (i < n - 1) cur_hp[i] -= att[i + 1];
            hps.insert({cur_hp[i], i});
            cur.insert(i);
        }
        FOR (_, n) {
            set<ll> ded, upd;
            while (sz(hps)) {
                auto [d, i] = *hps.begin();
                if (d >= 0) break;
                ded.insert(i);
                hps.erase(hps.begin());
            }
            rv[_] = sz(ded);
            FORE (i, ded) {
                cur.erase(i);
            }
            FORE (i, ded) {
                auto it = cur.lower_bound(i);
                if (it != cur.begin()) upd.insert(*prev(it));
                if (it != cur.end()) upd.insert(*it);
            }
            FORE (i, upd) {
                hps.erase({cur_hp[i], i});
                cur_hp[i] = def[i];
                auto it = cur.find(i);
                if (it != cur.begin()) {
                    cur_hp[i] -= att[*prev(it)];
                }
                it++;
                if (it != cur.end()) {
                    cur_hp[i] -= att[*it];
                }
                hps.insert({cur_hp[i], i});
            }
        }
        FORE (x, rv) cout << x << ' ';
        cout << '\n';
    }

    return 0;
}