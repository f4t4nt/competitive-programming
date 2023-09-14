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

ll n;
ld d, s, t, fmn, fmx, l;

ld seg(ll del) {
    return sqrt(s * s + d * d * del * del);
}

ll solve(ll i, vector<bool> &vis, ld len) {
    if (i == 0) {
        if (l - len * 2 - s >= fmn * 2 && l - len * 2 - s <= fmx * 2) {
            return 1;
        } else {
            return 0;
        }
    }
    vis[i] = true;
    ll rv = 0;
    if (i != n - 1 && !vis[i + 1]) {
        rv += solve(i + 1, vis, len + d + t);
    }
    if (!vis[i - 1]) {
        rv += solve(i - 1, vis, len + d + t);
    }
    FOR (j, n) {
        if (!vis[j]) {
            rv += solve(j, vis, len + seg(i - j) + t);
        }
    }
    vis[i] = false;
    return rv;
}

int main() {
    cin >> n >> d >> s >> t >> fmn >> fmx;
    while (cin >> l) {
        vector<bool> vis(n);
        cout << solve(n - 1, vis, t) << '\n';
    }

    return 0;
}