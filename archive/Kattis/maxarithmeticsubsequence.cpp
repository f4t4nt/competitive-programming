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
    cin.tie(0);
    cout.tie(0);

    ll t;
    cin >> t;
    while (t--) {
        ll n, c;
        cin >> n >> c;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
        }
        ll rv = 0;
        vector<set<ll>> vis(n);
        FOR (i, n) {
            FOB (j, i + 1, min(n, i + c + 1)) {
                ll diff = a[j] - a[i],
                    val_lo = a[i] - diff,
                    val_hi = a[j] + diff,
                    len = 2;
                if (vis[i].count(diff)) {
                    continue;
                }
                vis[i].insert(diff);
                vis[j].insert(diff);
                ll idx = j;
                while (idx < n && a[idx] <= val_hi) {
                    if (a[idx] == val_hi) {
                        len++;
                        val_hi += diff;
                        vis[idx].insert(diff);
                    }
                    idx++;
                }
                idx = i;
                while (idx >= 0 && a[idx] >= val_lo) {
                    if (a[idx] == val_lo) {
                        len++;
                        val_lo -= diff;
                        vis[idx].insert(diff);
                    }
                    idx--;
                }
                rv = max(rv, len);
            }
        }
        cout << (rv > n / c ? rv : -1) << '\n';
    }

    return 0;
}