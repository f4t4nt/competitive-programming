#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using cd = complex<long double>;
using ld = long double;
using ch = char;
using str = string;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

using indexed_set = tree<
    ll,
    null_type,
    less<ll>,
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

ll mex(set<ll> &s) {
    ll i = 0;
    while (s.count(i)) {
        i++;
    }
    return i;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<ll> dp(3);
    FOB (i, 3, 2e3 + 1) {
        set<ll> s;
        FOB (j, 1, (i + 1) / 2) {
            s.insert(dp[j] ^ dp[i - j]);
        }
        dp.pb(mex(s));
    }

    ll t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        if (n >= 2e3) {
            cout << "first\n";
        } else {
            cout << (dp[n] ? "first" : "second") << '\n';
        }
    }

    return 0;
}