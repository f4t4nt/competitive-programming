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
        ll n, q, sum = 0;
        cin >> n >> q;
        set<ll> ones;
        vector<ll> a(n);
        FOR (i, n) {
            cin >> a[i];
            sum += a[i];
            if (a[i] == 1) ones.insert(i);
        }
        while (q--) {
            ll qt;
            cin >> qt;
            if (qt == 1) {
                ll s;
                cin >> s;
                if ((sum - s) % 2 == 0) {
                    if (sum >= s) cout << "YES\n";
                    else cout << "NO\n";
                } else {
                    if (sz(ones)) {
                        ll tmp = sum - 1 - 2 * min(*ones.begin(), n - 1 - *ones.rbegin());
                        if (tmp >= s) cout << "YES\n";
                        else cout << "NO\n";
                    } else cout << "NO\n";
                }
            } else {
                ll i, v;
                cin >> i >> v;
                i--;
                if (a[i] != v) {
                    if (v == 1) ones.insert(i);
                    else ones.erase(i);
                    sum += v - a[i];
                    a[i] = v;
                }
            }
        }
    }

    return 0;
}