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

    str s, rv;
    cin >> s;
    flip(s);
    ll n = sz(s);
    vector<int> bits;
    FORE (c, s) {
        ll x = c - '0';
        FOR (i, 3) {
            bits.pb(x & 1);
            x >>= 1;
        }
    }
    n = sz(bits);
    for (ll i = 0; i < n; i += 4) {
        ll x = 0;
        for (ll j = i; j < i + 4 && j < n; j++) x |= bits[j] << (j - i);
        rv.pb(x < 10 ? x + '0' : x - 10 + 'A');
    }
    while (sz(rv) && rv.back() == '0') rv.pop_back();
    flip(rv);
    if (sz(rv) == 0) rv = "0";
    cout << rv << '\n';

    return 0;
}