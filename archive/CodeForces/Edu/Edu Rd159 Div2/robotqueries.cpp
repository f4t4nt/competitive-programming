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

pair<vector<pair<ll, ll>>, map<pair<ll, ll>, set<ll>>> get_vis(str s) {
    ll x = 0, y = 0;
    vector<pair<ll, ll>> vis = {{x, y}};
    map<pair<ll, ll>, set<ll>> mp;
    mp[{x, y}].insert(0);
    FOR (i, sz(s)) {
        if (s[i] == 'U') y++;
        elif (s[i] == 'D') y--;
        elif (s[i] == 'L') x--;
        elif (s[i] == 'R') x++;
        vis.pb({x, y});
        mp[{x, y}].insert(i + 1);
    }
    return {vis, mp};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    ll n, q;
    cin >> n >> q;
    str s;
    cin >> s;
    ll x = 0, y = 0;
    auto [vis, mp] = get_vis(s);
    while (q--) {
        ll qx, qy, l, r;
        cin >> qx >> qy >> l >> r;
        l--, r--;

        // str sq = s;
        // ll i = l, j = r;
        // while (i < j) {
        //     swap(sq[i], sq[j]);
        //     i++, j--;
        // }
        // auto [visq, mpq] = get_vis(sq);
        // cout << (mpq.count({qx, qy}) ? "YES" : "NO") << '\n';

        if (mp.count({qx, qy})) {
            if (*mp[{qx, qy}].begin() <= l || *mp[{qx, qy}].rbegin() > r) {
                cout << "YES\n";
                continue;
            }
        }
        ll nx = vis[l].first + vis[r + 1].first - qx,
              ny = vis[l].second + vis[r + 1].second - qy;
        if (mp.count({nx, ny})) {
            auto it = mp[{nx, ny}].lower_bound(l);
            if (it != mp[{nx, ny}].end() && *it <= r) {
                cout << "YES\n";
                continue;
            }
        }
        cout << "NO\n";
    }

    return 0;
}