#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef complex<long double> cd;
typedef long double ld;
typedef char ch;
typedef string str;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while (true) {
        ll n, m;
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        vector<pair<ll, ll>> calls(n), chks(m);
        FOR(i, n) {
            ll src, dst;
            cin >> src >> dst >> calls[i].first >> calls[i].second;
            calls[i].second += calls[i].first;
        }
        FOR(i, m) {
            cin >> chks[i].first >> chks[i].second;
            chks[i].second += chks[i].first;            
        }
        FORE (chk, chks) {
            ll rv = 0;
            FORE (call, calls) {
                if (max(call.first, chk.first) < min(call.second, chk.second)) {
                    rv++;
                }
            }
            cout << rv << '\n';
        }
    }

    return 0;
}