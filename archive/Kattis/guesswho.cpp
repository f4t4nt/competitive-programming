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
    set<pair<ll, str>> rv;
    vector<str> ppl(n);
    FOR (i, n) {
        cin >> ppl[i];
        rv.insert({i + 1, ppl[i]});
    }
    while (q--) {
        ll idx; ch c;
        cin >> idx >> c;
        idx--;
        set<pair<ll, str>> nv;
        for (auto [i, s] : rv) if (s[idx] == c) nv.insert({i, s});
        rv = nv;
    }
    if (sz(rv) == 1) {
        cout << "unique\n" << rv.begin()->first << '\n';
    } else {
        cout << "ambiguous\n" << sz(rv) << '\n';
    }

    return 0;
}