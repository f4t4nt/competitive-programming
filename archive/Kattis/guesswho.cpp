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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, m, q;
    cin >> n >> m >> q;
    multiset<str> strs;
    map<str, ll> id;
    FOR (i, n) {
        str s;
        cin >> s;
        strs.insert(s);
        id[s] = i;
    }
    while (q--) {
        ll idx;
        ch c;
        cin >> idx >> c;
        idx--;
        multiset<str> new_strs;
        FORE (s, strs) {
            if (s[idx] == c) {
                new_strs.insert(s);
            }
        }
        strs = new_strs;
    }
    if (sz(strs) > 1) cout << "ambiguous\n" << sz(strs) << '\n';
    elif (sz(strs) == 0) assert(false);
    else cout << "unique\n" << id[*strs.begin()] + 1 << '\n';

	return 0;
}