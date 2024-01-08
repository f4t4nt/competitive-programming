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
        ll n, x;
        cin >> n >> x;
        vector<pair<ll, ll>> a(n), b(n);
        FOR (i, n) {
            cin >> a[i].first;
            a[i].second = i;
        }
        FOR (i, n) {
            cin >> b[i].first;
            b[i].second = i;
        }
        ssort(a);
        ssort(b);
        ll i = 0, j = x % n, y = 0;
        while (i < n) {
            if (a[i].first > b[j].first) {
                y++;
            }
            i++;
            j = (j + 1) % n;
        }
        if (x == y) {
            cout << "YES\n";
            vector<ll> rv(n);
            FOR (i, n) {
                rv[a[i].second] = b[(i + x) % n].first;
            }
            FOR (i, n) {
                cout << rv[i] << ' ';
            }
            cout << '\n';
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}