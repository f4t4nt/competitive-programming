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

    str f1 = "F_in_Finals_stands_for_Fizz_Buzz!";
    vector<str> ref = {"F"};
    FOR (i, 10) {
        str tmp = "";
        FORE (c, ref.back()) {
            if (c == 'F') {
                tmp += f1;
            } else {
                tmp += c;
            }
        }
        ref.pb(tmp);
    }
    vector<ll> szs = {1};
    while (szs.back() < 1e18) {
        szs.pb(szs.back() * 3 + 30);
    }

    ll q;
    cin >> q;
    while (q--) {
        ll i = 0, idx, depth;
        cin >> idx >> depth;
        depth++;
        depth = min(depth, sz(szs));
        idx--;
        if (idx >= szs[depth]) {
            cout << '?';
            continue;
        }
        while (idx > 0) {
            assert(i < sz(f1));
            if (f1[i] == 'F') {
                assert(depth > 0);
                if (idx < szs[depth - 1]) {
                    depth--;
                    i = 0;
                } else {
                    idx -= szs[depth - 1];
                    i++;
                }
            } else {
                i++;
                idx--;
            }
        }
        cout << f1[i];
    }

    return 0;
}