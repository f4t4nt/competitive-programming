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

    ll tc;
    cin >> tc;
    while (tc--) {
        ll n, p, l, t;
        cin >> n >> p >> l >> t;
        ll task_cnt = (n + 6) / 7;
        ll max_cram = task_cnt / 2 * (2 * t + l);
        if (max_cram >= p) {
            cout << n - (p + 2 * t + l - 1) / (2 * t + l) << '\n';
            continue;
        }
        ll rv = task_cnt / 2;
        if (task_cnt % 2 == 1) {
            max_cram += t + l;
            rv++;
            if (max_cram >= p) {
                cout << n - rv << '\n';
                continue;
            }
        }
        cout << n - (p - max_cram + l - 1) / l - rv << '\n';
    }

    return 0;
}