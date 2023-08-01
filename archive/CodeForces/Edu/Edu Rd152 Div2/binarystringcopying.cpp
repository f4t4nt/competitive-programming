#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n, m;
        cin >> n >> m;
        str s;
        cin >> s;
        set<ll> pos0, pos1;
        FOR (i, n) {
            if (s[i] == '0') {
                pos0.insert(i);
            } else {
                pos1.insert(i);
            }
        }
        pos0.insert(-1), pos0.insert(n);
        pos1.insert(-1), pos1.insert(n);
        vector<pair<ll, ll>> ops(m), ops_mod(m);
        FOR (i, m) {
            cin >> ops[i].first >> ops[i].second;
            ops[i].first--, ops[i].second--;
        }
        FOR (i, m) {
            auto &op = ops[i];
            ll left = -1, right = -1;
            // find last 0 before op.second and first 1 after op.first
            auto it0 = pos0.upper_bound(op.second);
            if (it0 != pos0.begin()) {
                it0--;
            }
            auto it1 = pos1.lower_bound(op.first);
            ll idx0 = *it0, idx1 = *it1;
            // check *it0 <= op.second and *it1 >= op.first
            if (idx0 <= op.second && idx1 >= op.first) {
                // check if out of order
                if (idx0 > idx1) {
                    // find first 0 after op.second and last 1 before op.first
                    auto it0_2 = pos0.lower_bound(op.second + 1);
                    auto it1_2 = pos1.lower_bound(op.first);
                    assert(it1_2 != pos1.begin());
                    it1_2--;
                    // [left, right] = [it1_2 + 1, it0_2 - 1]
                    left = *it1_2 + 1, right = *it0_2 - 1;
                }
            }
            ops_mod[i] = {left, right};
        }
        set<pair<ll, ll>> ops_s;
        FORE (op, ops_mod) {
            ops_s.insert(op);
        }
        cout << sz(ops_s) << '\n';
    }

    return 0;
}