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

bool sum4(ll x, vector<ll> &a, vector<ll> &rv) {
    map<ll, set<vector<ll>>> pos;
    FOR (i, sz(a)) {
        FOB (j, i + 1, sz(a)) {
            pos[a[i] + a[j]].insert({i, j});
        }
    }
    FOR (i, sz(a)) {
        FOB (j, i + 1, sz(a)) {
            pos[a[i] + a[j]].erase({i, j});
        }
        FOB (j, i + 1, sz(a)) {
            ll y = x - a[i] - a[j];
            if (pos.count(y)) {
                FORE (v, pos[y]) {
                    if (v[0] > j) {
                        rv = {i, j, v[0], v[1]};
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll n, x;
    cin >> n >> x;
    vector<ll> a(n);
    FORE (y, a) {
        cin >> y;
    }
    vector<ll> rv;
    if (sum4(x, a, rv)) {
        FORE (y, rv) {
            cout << y + 1 << ' ';
        }
        cout << '\n';
    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}