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
        ll n, m;
        cin >> n >> m;
        vector<ll> a(n), b(m);
        vector<ll> bita(32), bitb(32), mn(32), mx(32);
        FOR (i, n) {
            cin >> a[i];
            FOR (j, 32) {
                if (a[i] & (1 << j)) {
                    bita[j] ^= 1;
                }
            }
        }
        mn = mx = bita;
        FOR (i, m) {
            cin >> b[i];
            FOR (j, 32) {
                if (b[i] & (1 << j)) {
                    bitb[j]++;
                }
            }
        }
        if (n & 1) { // odd, applying b sets bit to 1
            FOR (i, 32) {
                if (bitb[i] > 0) {
                    mx[i] = 1;
                }
            }
        } else { // even, applying b sets bit to 0
            FOR (i, 32) {
                if (bitb[i] > 0) {
                    mn[i] = 0;
                }
            }
        }
        ll rvmn = 0, rvmx = 0;
        FOR (i, 32) {
            if (mn[i]) {
                rvmn += (1 << i);
            }
            if (mx[i]) {
                rvmx += (1 << i);
            }
        }
        cout << rvmn << ' ' << rvmx << '\n';
    }

    return 0;
}