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
 
constexpr ll MOD = 1e9 + 7;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    ll n, tot = 0;
    cin >> n;
    vector<pair<ll, ll>> deg(n), rv;
    FOR (i, n) {
        cin >> deg[i].first;
        tot += deg[i].first;
        deg[i].second = i;
    }
    if (tot % 2 == 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    rsort(deg);
    ll last = 0;
    FOR (i, n) {
        sort(deg.begin() + i, deg.begin() + last, greater<>());
        auto [d, v] = deg[i];
        ll j = i + 1;
        while (j < n && d > 0) {
            if (deg[j].first > 0) {
                deg[j].first--;
                rv.pb({v, deg[j].second});
                d--;
            }
            j++;
        }
        if (d > 0) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        last = min(n, max(last, j + deg[i].first));
    }
    cout << sz(rv) << '\n';
    FORE (e, rv) {
        cout << e.first + 1 << ' ' << e.second + 1 << '\n';
    }
 
    return 0;
}