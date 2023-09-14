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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll n, xum = 0, rv = 0;
    cin >> n;
    vector<ll> a(n);
    set<ll> prev;
    prev.insert(0);
    FORE (x, a) {
        cin >> x;
        xum ^= x;
        ll i = 1 << 30, target = 0;
        while (i) {
            if ((xum & i) != i) {
                ll tmp = target | i;
                auto it = prev.lower_bound(tmp);
                if (it != prev.end() && (*it ^ tmp) < i) {
                    target = tmp;
                }
            }
            i >>= 1;
        }
        rv = max(rv, *prev.lower_bound(target) ^ xum);
        prev.insert(xum);
    }
    cout << rv << '\n';

    return 0;
}