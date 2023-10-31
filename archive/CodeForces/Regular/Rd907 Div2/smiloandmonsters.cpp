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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
        }
        ssort(a);
        ll lo = 0, hi = n - 1, sum = 0, rv = 0;
        while (lo <= hi) {
            while (lo < hi && sum + a[lo] <= a[hi]) {
                sum += a[lo];
                a[lo] = 0;
                lo++;
            }
            if (lo == hi) {
                // sum + x == a[hi] - x
                // x = (a[hi] - sum + 1) / 2
                ll del = (a[hi] - sum + 1) / 2;
                sum += del;
                a[lo] -= del;
            } else {
                a[lo] -= a[hi] - sum;
                sum = a[hi];
            }
            rv += sum;
            if (a[hi] > 0) {
                rv++;
                a[hi] = 0;
            }
            hi--;
            sum = 0;
        }
        cout << rv << '\n';
    }

    return 0;
}